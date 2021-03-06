/**
 * This file is generated by jsonrpcstub, DO NOT CHANGE IT MANUALLY!
 */

#ifndef JSONRPC_CPP_STUB_SCRABBLECLIENTSTUB_H_
#define JSONRPC_CPP_STUB_SCRABBLECLIENTSTUB_H_

#include <jsonrpccpp/client.h>

class ScrabbleClientStub : public jsonrpc::Client
{
    public:
        ScrabbleClientStub(jsonrpc::IClientConnector &conn, jsonrpc::clientVersion_t type = jsonrpc::JSONRPC_CLIENT_V2) : jsonrpc::Client(conn, type) {}

        Json::Value RegistrationService_Register(const std::string& botname, const std::string& botversion, const std::string& description, const std::string& game, const std::string& programminglanguage, const std::string& rpcendpoint, const std::string& token, const std::string& website) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["botname"] = botname;
            p["botversion"] = botversion;
            p["description"] = description;
            p["game"] = game;
            p["programminglanguage"] = programminglanguage;
            p["rpcendpoint"] = rpcendpoint;
            p["token"] = token;
            p["website"] = website;
            Json::Value result = this->CallMethod("RegistrationService.Register",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
        Json::Value Scrabble_Ready(const std::string& dictionary, const std::string& gameboard, int gameid, const std::string& letters) throw (jsonrpc::JsonRpcException)
        {
            Json::Value p;
            p["dictionary"] = dictionary;
            p["gameboard"] = gameboard;
            p["gameid"] = gameid;
            p["letters"] = letters;
            Json::Value result = this->CallMethod("Scrabble.Ready",p);
            if (result.isObject())
                return result;
            else
                throw jsonrpc::JsonRpcException(jsonrpc::Errors::ERROR_CLIENT_INVALID_RESPONSE, result.toStyledString());
        }
};

#endif //JSONRPC_CPP_STUB_SCRABBLECLIENTSTUB_H_
