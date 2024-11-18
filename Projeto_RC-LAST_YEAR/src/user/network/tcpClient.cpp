#include "tcpClient.hpp"

TcpClient::TcpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;

    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sockfd < 0) {
        throw ConnectionSetupError();
    }

    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->serverPort);
    this->serverAddr.sin_addr.s_addr = inet_addr(this->serverIP.c_str());

    if (connect(this->sockfd, (struct sockaddr *)&this->serverAddr, sizeof(this->serverAddr)) < 0) {
        throw ConnectionFailedError();
    }
}

int TcpClient::sendData(const string &data) {
    if(TCP_VERBOSE) printf("Sending data: %s", data.c_str());

    int n = write(this->sockfd, data.c_str(), data.length());

    if (n < 0) {
        throw ConnectionFailedError();
    }

    return n;
}

string TcpClient::receiveData() {
    struct timeval tv;
    tv.tv_sec = CONNECTION_TIMEOUT;
    tv.tv_usec = 0;

    // Set timeout for receiving data
    if(setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        throw ConnectionSetupError();
    }

    string dataReceived = "";

    // n is the number of bytes read, set to 1 to enter the loop
    int n = 1;

    int totalBytes = 0;


    // loops until there is no more data to read
    // add data being read to dataReceived string
    while(n != 0) {
        char buffer[CHUNCKS];
        n = read(this->sockfd, buffer, sizeof(buffer));

        if(n < 0) {
            // check if error is because of timeout
            if(tv.tv_sec == CONNECTION_TIMEOUT) {
                throw ConnectionTimeoutError();
            }

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

    if(TCP_VERBOSE) printf("Received data: %s\n", dataReceived.c_str());

    return dataReceived;
}