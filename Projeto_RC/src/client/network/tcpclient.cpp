#include "tcpclient.hpp"

// Constructor: Initializes the TCP client with the given IP and port, and sets up the connection.
TcpClient::TcpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;
    
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP socket
    
    int status = getaddrinfo(this->serverIP.c_str(), std::to_string(this->serverPort).c_str(), &hints, &res);
    if (status != 0) {
        throw ConnectionSetupError(); // Handle address resolution errors.
    }
    
    this->sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (this->sockfd < 0) {
        freeaddrinfo(res); // Free resources in case of error.
        throw ConnectionSetupError();
    }
    memcpy(&this->serverAddr, res->ai_addr, res->ai_addrlen);
    
    status = connect(this->sockfd, res->ai_addr, res->ai_addrlen);
    if (status < 0) {
        freeaddrinfo(res); // Free resources in case of error.
        throw ConnectionFailedError();
    }

    freeaddrinfo(res); // Free resources after successful setup.
}

// Sends data to the server over the established TCP connection.
int TcpClient::sendData(const string &data) {
    int n = write(this->sockfd, data.c_str(), data.length());

    if (n < 0) {
        throw ConnectionFailedError(); // Handle errors during data transmission.
    }

    return n; // Return the number of bytes sent.
}

// Receives data from the server over the TCP connection.
string TcpClient::receiveData() {
    string dataReceived = ""; 

    int n = 1; // Number of bytes read in each iteration.
    int totalBytes = 0; // Total number of bytes received.

    // Loop to read data from the socket until there's no more data.
    while (n != 0) {
        char buffer[MAX_TCP_REPLY_SIZE];
        n = read(this->sockfd, buffer, sizeof(buffer));

        if (n < 0) {
            throw ConnectionFailedError(); // Handle errors during data reception.
        }

        totalBytes += n;

        if (totalBytes > MAX_TCP_REPLY_SIZE) {
            throw FileSizeError(); // Handle excessive data size.
        }

        dataReceived.append(buffer, n); // Append received data to the string.
    }

    // Remove trailing /n character from the received string.
    dataReceived = dataReceived.substr(0, dataReceived.length() - 1);

    return dataReceived; // Return the content
}
