/* 
 * File:   HTTPDownload.h
 * Author: pi
 *
 * Created on 19 June 2016, 2:35 PM
 */

#ifndef HTTPDOWNLOADREQUEST_H
#define	HTTPDOWNLOADREQUEST_H
#include <iostream>
#include <fstream>

class HTTPDownloadRequest {
public:
    HTTPDownloadRequest(std::string filename);
    virtual ~HTTPDownloadRequest();
    
    bool Download(std::string sourceUrl, std::string sha1, long timeout = 30);
private:
    std::ofstream os;
};

#endif	/* HTTPDOWNLOAD_H */

