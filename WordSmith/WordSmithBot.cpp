/* 
 * File:   WordSmithBot.cpp
 * Author: pi
 * 
 * Created on 8 June 2016, 11:21 PM
 */
#include "WordSmithBot.h"
#include "HTTPDownloadRequest.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <jsoncpp/json/json.h>
#include <thread>
#include <fstream>
using namespace std;

static bool hashMatch[3];
static string hashes[3];

void DownloadFiles(int gameid, WordSmithBot* bot, string dic_url, string board_url, string letters_url);

WordSmithBot::WordSmithBot(AbstractServerConnector &connector, serverVersion_t type)
: ScrabbleServerStub(connector, type) {
}

WordSmithBot::~WordSmithBot() {
    delete scrabbleClient;
}

void WordSmithBot::StartBot(string endpoint, string token)
{
    HttpClient httpClient("http://merknera.com");
    scrabbleClient = new ScrabbleClientStub(httpClient, JSONRPC_CLIENT_V2);
    
    string botname = "WordSmith";
    string botversion = "1.0.0";
    string description = "Forges words from letters.";
    string game = "SCRABBLE";
    string programminglanguage = "C++";
    string website = "http://github.com/apigram/wordsmith-omega";
    
    scrabbleClient->RegistrationService_Register(botname, botversion, description, game, programminglanguage, endpoint, token, website);
}

Json::Value WordSmithBot::Status_Ping()
{
    Json::Value result;
    result["status"] = "OK";
    
    return result;
}

Json::Value WordSmithBot::Scrabble_NewGame(const Json::Value& dictionary, const Json::Value& gameboard, int gameid, const Json::Value& letters, const std::string& players)
{
    Json::Value result;
    string dic_url = dictionary["url"].asString();
    string board_url = gameboard["url"].asString();
    string letters_url = letters["url"].asString();
    ifstream fileCache;
    string sha1;
    int counter = 0;
    
    hashes[0] = dictionary["sha1"].asString();
    hashes[1] = gameboard["sha1"].asString();
    hashes[2] = letters["sha1"].asString();
    
    fileCache.open("cache.txt");
    
    // check the sha1 hash for the dictionary.
    do {
        fileCache >> sha1;
        hashMatch[counter] = (hashes[counter] != sha1);
        counter++;
    } while (!fileCache.eof() && counter < 3);
    fileCache.close();
    
    thread t(DownloadFiles, gameid, this, dic_url, board_url, letters_url);
    t.detach();
    
    if (hashMatch[0] == true || hashMatch[1] == true || hashMatch[2] == true)
        result["status"] = "PENDING";
    else
        result["status"] = "READY";
    return result;
}

Json::Value WordSmithBot::Scrabble_NextMove(int gameid, const Json::Value& gamestate, const Json::Value& tiles)
{
    
}

void WordSmithBot::Ready(int gameid)
{
    scrabbleClient->Scrabble_Ready(hashes[0], hashes[1], gameid, hashes[2]);
}

void WordSmithBot::SetBoard(Json::Value board)
{
    this->gameboard = board;
}

void WordSmithBot::SetDictionary(Json::Value dictionary)
{
    this->dictionary = dictionary;
}

void WordSmithBot::SetLetters(Json::Value letters)
{
    this->letters = letters;
}

// Called by thread.
void DownloadFiles(int gameid, WordSmithBot* bot, string dic_url, string board_url, string letters_url)
{
    ofstream fileCache;
    
    fileCache.open("cache.txt", ios::trunc);
    if (hashMatch[0] == true)
    {
        HTTPDownloadRequest* request = new HTTPDownloadRequest("dictionary.json");
        if (request->Download(dic_url, hashes[0]))
        {
            // Download successful. Load the new file into the system.
            ifstream is;
            Json::Reader reader;
            Json::Value val;
            
            is.open("dictionary.json");
            reader.parse(is, val, false);
            bot->SetDictionary(val);
            is.close();
        }
        else
        {
            // download failed.
        }
        delete request;
    }
    if (hashMatch[1] == true)
    {
        HTTPDownloadRequest* request = new HTTPDownloadRequest("gameboard.json");
        if (request->Download(board_url, hashes[1]))
        {
            // download successful.
            ifstream is;
            Json::Reader reader;
            Json::Value val;
            
            is.open("gameboard.json");
            reader.parse(is, val, false);
            bot->SetBoard(val);
            is.close();
        }
        else
        {
            // download failed.
        }
        delete request;
    }
    if (hashMatch[2] == true)
    {
        HTTPDownloadRequest* request = new HTTPDownloadRequest("letters.json");
        if (request->Download(letters_url, hashes[2]))
        {
            // download successful
            ifstream is;
            Json::Reader reader;
            Json::Value val;
            
            is.open("letters.json");
            reader.parse(is, val, false);
            bot->SetLetters(val);
            is.close();
        }
        else
        {
            // download failed.
        }
        delete request;
    }
    fileCache << hashes[0] << endl << hashes[1] << endl << hashes[2];
    fileCache.flush();
    fileCache.close();
    
    bot->Ready(gameid);
}

