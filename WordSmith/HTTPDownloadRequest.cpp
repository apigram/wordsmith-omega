/* 
 * File:   HTTPDownload.cpp
 * Author: pi
 * 
 * Created on 19 June 2016, 2:35 PM
 */

#include "HTTPDownloadRequest.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <fstream>

static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp);

using namespace std;

HTTPDownloadRequest::HTTPDownloadRequest(string filename) {
    curl_global_init(CURL_GLOBAL_ALL);
    os.open(filename);
}

HTTPDownloadRequest::~HTTPDownloadRequest() {
    curl_global_cleanup();
    os.flush();
    os.close();
}

bool HTTPDownloadRequest::Download(string sourceUrl, string sha1, long timeout)
{
    CURLcode code(CURLE_FAILED_INIT);
    CURL* curl = curl_easy_init();
    
    if (curl)
    {
        if (CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_write))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_FILE, &os))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
                && CURLE_OK == (code = curl_easy_setopt(curl, CURLOPT_URL, sourceUrl.c_str()))
                )
        {
            code = curl_easy_perform(curl);
        }
        curl_easy_cleanup(curl);
        curl = 0;
    }
    if (code == CURLE_OK)
    {
        return true;
    }
    return false;
}

static size_t data_write(void* buf, size_t size, size_t nmemb, void* userp)
{
    if (userp)
    {
        ostream& os = *static_cast<ostream*>(userp);
        streamsize len = size * nmemb;
        if (os.write(static_cast<char*>(buf), len))
        {
            return len;
        }
    }
    return 0;
}

