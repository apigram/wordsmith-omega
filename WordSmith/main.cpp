/* 
 * File:   main.cpp
 * Author: pi
 *
 * Created on 8 June 2016, 10:35 PM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "WordSmithBot.h"
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    HttpServer httpServer(8080);
    WordSmithBot bot(httpServer, JSONRPC_SERVER_V2);
    
    bot.StartBot("10.0.0.32", "SlyO2HvTRXMXw2D1VnWbcuzKWdbk2wGbaywab5cYYBgwYj1mux");
    
    bot.StartListening();
    
    cout << "Press enter to stop the server..." << endl;
    getchar();
    bot.StopListening();
    
    return 0;
}

