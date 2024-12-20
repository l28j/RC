#include "udpSocket.hpp"

// Constructor: Initializes a new UDP socket for monitoring connections.
UdpSocket::UdpSocket(int port, bool verbose) {
    this->port = port;
    this->verbose = verbose;

    // Create a socket for UDP communication.
    this->monitorSocketfd = socket(AF_INET, SOCK_DGRAM, 0);
    this->commandSocketfd = this->monitorSocketfd; // For UDP, the monitor and command sockets are the same.

    if (this->monitorSocketfd < 0) {
        printf("Error creating socket\n"); // print error if socket creation fails.
    }

    // Set server information, including the port.
    this->serverInfo.sin_port = htons(this->port);

    // Bind the socket to the specified port.
    int err = bind(this->monitorSocketfd, (struct sockaddr*)&this->serverInfo, sizeof(this->serverInfo));
    if (err < 0) {
        printf("Error binding socket to port %d\n", this->port); // print error if binding fails.
    }
}

// Constructor: Initializes a UDP socket using an existing connection.
UdpSocket::UdpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
    this->port = port;
    this->verbose = verbose;
    this->monitorSocketfd = socketfd;
    this->commandSocketfd = socketfd;
    this->serverInfo = serverInfo;
    this->clientInfo = clientInfo;
}

// Receives data from a client.
string UdpSocket::receiveData() {
    char buffer[MAX_MESSAGE_SIZE] = {0}; // Initialize the buffer with zeros.
    socklen_t len = sizeof(this->clientInfo);

    // Receive data and store the number of bytes received.
    int n = recvfrom(this->monitorSocketfd, buffer, MAX_MESSAGE_SIZE, 0, (struct sockaddr*)&this->clientInfo, &len);
    if (n < 0) {
        return ""; // Return an empty string in case of an error.
    }

    // Create a string with the received bytes.
    string dataReceived(buffer, n);

    // Remove the trailing '\n' character, if present.
    if (!dataReceived.empty() && dataReceived.back() == '\n') {
        dataReceived.pop_back();
    }

    if (this->verbose) {  //if verbose mode is activated, server terminal prints confirmation
        printf("[UDP] Received: %s\n", dataReceived.c_str());
    }

    return dataReceived;
}

// Sends data to the client.
void UdpSocket::sendData(string data) {
    int n = sendto(this->commandSocketfd, data.c_str(), data.length(), 0, (struct sockaddr*)&this->clientInfo, sizeof(this->clientInfo));

    if (n < 0) {
        printf("Error sending data\n"); // print an error if sending fails.
    }

    if (this->verbose) {  //if verbose mode is activated, server terminal prints confirmation
        printf("[PROTOCOL] Sent data: %s\n", data.c_str()); 
    }
}
