#include "udpclient.hpp"
#include "../errors.hpp"
#include "../constants.hpp"

#define MAX_MESSAGE_SIZE 1024


UdpClient::UdpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;
    
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_DGRAM;  // UDP socket

    int status = getaddrinfo(this->serverIP.c_str(), std::to_string(this->serverPort).c_str(), &hints, &res);
    if (status != 0) {
        throw ConnectionSetupError();
    }

    this->sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (this->sockfd < 0) {
        freeaddrinfo(res);
        throw ConnectionSetupError();
    }
    
    memcpy(&this->serverAddr, res->ai_addr, res->ai_addrlen);

    freeaddrinfo(res);
}

    

int UdpClient::sendData(const string& data) {
   
    int n = sendto(this->sockfd, data.c_str(), data.length(), 0, (struct sockaddr*) &this->serverAddr, sizeof(this->serverAddr));

    if(n < 0) {
        throw ConnectionFailedError();
    }

    return n;
}

string UdpClient::receiveData() {
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS;
    timeout.tv_usec = TIMEOUT_MICROSECONDS;   

    if (setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        throw std::runtime_error("Failed to set socket timeout");
    }

    char buffer[MAX_MESSAGE_SIZE];
    socklen_t len = sizeof(this->serverAddr);
    int n = recvfrom(this->sockfd, buffer, MAX_MESSAGE_SIZE, 0, (struct sockaddr*)&this->serverAddr, &len);

    if (n < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            throw std::runtime_error("Connection Timed out. Please try again!");
        } else {
            throw ConnectionFailedError();
        }
    }

    // Remove the newline character if present
    buffer[n-1] = '\0';

    string dataReceived = string(buffer);
    return dataReceived;
}