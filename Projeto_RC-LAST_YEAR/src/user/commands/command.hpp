#ifndef USER_COMMAND_H
#define USER_COMMAND_H

#include "../../common/common.hpp"
#include "../clientState.hpp"

#include "../network/networkClient.hpp"
#include "../network/udpClient.hpp"
#include "../network/tcpClient.hpp"

#include "../constants.hpp"

#include <memory>

using namespace std;

/*
Command Abstract Class
All common methods and attributes for commands are defined here
*/
class Command {
    protected:
        ClientState* clientState;
        unique_ptr<NetworkClient> networkClient;

        int networkType;

        string command;

    public:
        Command(string command) 
            : command(command) {}

        Command(int networkType, string command) 
            : networkType(networkType), command(command) {}

        virtual ~Command() = default;

        // sends data to Auction Server
        virtual void send() = 0;

        // receives data from Auction Server
        virtual void receive() = 0;

        virtual int execute();

        // returns local command used
        string getCommand();

        // returns formatted string of data to send to auction server
        virtual string formatData() = 0;

        // pass client state to command
        void setClientState(ClientState* clientState);

        /* 
        define network client to use based on network type
        - UDP: UDPClient
        - TCP: TCPClient
        */
        void setNetworkClient(string serverIp, int serverPort);
};

#endif