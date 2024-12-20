#include "udpclient.hpp"
#include "../errors.hpp"
#include "../constants.hpp"

#define MAX_MESSAGE_SIZE 1024

// Constructor: Initializes the UDP client with the given IP and port.
UdpClient::UdpClient(string ip, int port) {
    this->serverIP = ip;
    this->serverPort = port;
    
    struct addrinfo hints, *res;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;  // IPv4
    hints.ai_socktype = SOCK_DGRAM;  // UDP socket

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

    freeaddrinfo(res); // Free resources after successful setup.
}

// Sends data to the server via UDP.
int UdpClient::sendData(const string& data) {
    int n = sendto(this->sockfd, data.c_str(), data.length(), 0, (struct sockaddr*) &this->serverAddr, sizeof(this->serverAddr));

    if (n < 0) {
        throw ConnectionFailedError(); // Handle errors during data transmission.
    }

    return n; // Return the number of bytes sent.
}

// Receives data from the server via UDP.
string UdpClient::receiveData() {
    struct timeval timeout;
    timeout.tv_sec = TIMEOUT_SECONDS; // Set receive timeout (seconds).
    timeout.tv_usec = TIMEOUT_MICROSECONDS; // Set receive timeout (microseconds).

    // Apply the timeout settings to the socket.
    if (setsockopt(this->sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0) {
        throw std::runtime_error("Failed to set socket timeout"); // Handle socket option errors.
    }

    char buffer[MAX_UDP_MESSAGE];
    socklen_t len = sizeof(this->serverAddr);
    int n = recvfrom(this->sockfd, buffer, MAX_UDP_MESSAGE, 0, (struct sockaddr*)&this->serverAddr, &len);

    if (n < 0) {
        if (errno == EWOULDBLOCK || errno == EAGAIN) {
            throw std::runtime_error("Connection Timed out. Please try again!"); // Handle timeout errors.
        } else {
            throw ConnectionFailedError(); // Handle other reception errors.
        }
    }

    // Remove the newline character if present.
    buffer[n - 1] = '\0';

    string dataReceived = string(buffer);
    return dataReceived; // Return the received data.
}
