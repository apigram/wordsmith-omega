/* 
 * File:   WordSmithBot.h
 * Author: pi
 *
 * Created on 8 June 2016, 11:21 PM
 */

#ifndef WORDSMITHBOT_H
#define	WORDSMITHBOT_H

#include "scrabbleclientstub.h"
#include "scrabbleserverstub.h"
#include <string>
#include <set>

using namespace jsonrpc;

class WordSmithBot : public ScrabbleServerStub {
public:
    WordSmithBot(AbstractServerConnector &connector, serverVersion_t type);
    virtual ~WordSmithBot();
    
    void StartBot(std::string endpoint, std::string token);
    void Ready(int gameid);
    void SetBoard(Json::Value board);
    void SetDictionary(Json::Value dictionary);
    void SetLetters(Json::Value letters);
private:
    virtual Json::Value Status_Ping();
    virtual Json::Value Scrabble_NewGame(const Json::Value& dictionary, const Json::Value& gameboard, int gameid, const Json::Value& letters, const std::string& players);
    virtual Json::Value Scrabble_NextMove(int gameid, const Json::Value& gamestate, const Json::Value& tiles);

    ScrabbleClientStub* scrabbleClient;
    
    Json::Value gameboard;
    Json::Value dictionary;
    Json::Value letters;
};

#endif	/* WORDSMITHBOT_H */

