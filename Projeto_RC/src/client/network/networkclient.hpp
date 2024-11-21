#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <string>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <unistd.h>

#include "../constants.hpp"
#include "../errors.hpp"

using namespace std;

/* 
Abstract class for network clients 
All methods of network clients are defined here
*/
class NetworkClient {
    public:
        ~NetworkClient();
        virtual int sendData(const string& data) = 0;
        virtual string receiveData() = 0;

    protected:
        int sockfd = -1;
        string serverIP;
        int serverPort;

        struct sockaddr_in serverAddr;
};

#endif