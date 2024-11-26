#include "tcpclient.hpp"

TcpClient::TcpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;
    
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    
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

int TcpClient::sendData(const string &data) {
    
    int n = write(this->sockfd, data.c_str(), data.length());

    if (n < 0) {
        throw ConnectionFailedError();
    }

    return n;
}

string TcpClient::receiveData() {
   
    string dataReceived = "";

    // n is the number of bytes read, set to 1 to enter the loop
    int n = 1;

    int totalBytes = 0;


    // loops until there is no more data to read
    // add data being read to dataReceived string
    while(n != 0) {
        char buffer[MAX_TCP_REPLY_SIZE];
        n = read(this->sockfd, buffer, sizeof(buffer));

        if(n < 0) {
            throw ConnectionFailedError();
        }

        totalBytes += n;

        if(totalBytes > MAX_TCP_REPLY_SIZE) {
            throw FileSizeError();
        }

        dataReceived.append(buffer, n);
    }

    // remove \n from the end of the string
    dataReceived = dataReceived.substr(0, dataReceived.length() - 1);

    return dataReceived;
}