#include "main.hpp"

#include <iostream>

using namespace std;


int main(int argc, char** argv) {

    string serverIP = DEFAULT_IP;
    int serverPort = DEFAULT_PORT;

    for (int i = 0; i<argc; i++){
        string arg = argv[i];

        if (arg == IP_FLAG) {
            serverIP = argv[i+1];
        } else if (arg == PORT_FLAG) {
            serverPort = atoi(argv[i+1]);
        }
    }

    printf("Connecting to %s:%d\n", serverIP.c_str(), serverPort);

    ClientState clientState = ClientState();

    int exit = 0;

    while(!exit) {
        printf("\n> ");

        string input;

        getline(cin, input);

        Command* command;

        try {
            command = CommandParser::parseCommand(input);

            // There is no corresponding command for the input
            // or the command format is invalid
            if(command == nullptr) {
                continue;
            }

            command->setNetworkClient(serverIP, serverPort);

            command->setClientState(&clientState);

            exit = command->execute();
        } catch (const CostumError& e) {
            printf("%s\n", e.what());
        } catch (const exception& e) {
            printf("%s\n", string(UNKNOW_ERROR_MSG).c_str());
        }

        if(command != nullptr) {
            delete command;
        }
    }   

    return 0;
}