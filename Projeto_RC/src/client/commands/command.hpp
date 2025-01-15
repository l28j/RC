#ifndef USER_COMMAND_H
#define USER_COMMAND_H

#include "../../common/common.hpp"
#include "../client.hpp"

#include "../network/networkclient.hpp"
#include "../network/udpclient.hpp"
#include "../network/tcpclient.hpp"

#include "../constants.hpp"

#include <memory>

using namespace std;

/*
Command Abstract Class
All common methods and attributes for commands are defined here
*/

class Command {
    protected:
        Client* client;
        
        unique_ptr<NetworkClient> networkClient;

        int networkType;

        string command;

    public:
        Command(string command) 
            : command(command) {}

        Command(int networkType, string command) 
            : networkType(networkType), command(command) {}

        virtual ~Command() = default;

        virtual void send() = 0;

        virtual void receive() = 0;

        virtual int execute();

        // returns local command used
        string getCommand();

        virtual string formatData() = 0;

        // pass client state to command
        void setClient(Client* clientState);

        /* 
        define network client to use based on network type
        - UDP: UDPClient
        - TCP: TCPClient
        */
        void setNetworkClient(string serverIp, int serverPort);
};

#endif