#include "udpclient.hpp"
#include "../errors.hpp"
#include "../constants.hpp"

#define MAX_MESSAGE_SIZE 1024


UdpClient::UdpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;

    /*
    domain – Specifies the communication 
        domain ( AF_INET for IPv4/ AF_INET6 for IPv6 ) 
    type – Type of socket to be created 
        ( SOCK_STREAM for TCP / SOCK_DGRAM for UDP ) 
    protocol – Protocol to be used by the socket. 
        0 means using the default protocol for the address family.  
    */
    this->sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(this->sockfd < 0) {
        throw ConnectionSetupError();
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->serverPort);
    this->serverAddr.sin_addr.s_addr = inet_addr(this->serverIP.c_str());
}


int UdpClient::sendData(const string& data) {
   
    int n = sendto(this->sockfd, data.c_str(), data.length(), 0, (struct sockaddr*) &this->serverAddr, sizeof(this->serverAddr));

    if(n < 0) {
        throw ConnectionFailedError();
    }

    return n;
}

string UdpClient::receiveData() {

    char buffer[MAX_MESSAGE_SIZE];
    socklen_t len = sizeof(this->serverAddr);
    int n = recvfrom(this->sockfd, buffer, MAX_MESSAGE_SIZE, 0, (struct sockaddr*) &this->serverAddr, &len);

    if(n < 0) {
        throw ConnectionFailedError();
    }
    // Set to n-1 because of the \n, removing \n helps with parsing and printing
    buffer[n-1] = '\0';

    string dataReceived = string(buffer);

    return dataReceived;
}