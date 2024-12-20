#include "socket.hpp"

// Constructor for the Socket class
Socket::Socket() {
    // Initialize the server information structure
    serverInfo.sin_family = AF_INET;        // Set the address family to IPv4
    serverInfo.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface
}

// Destructor for the Socket class
Socket::~Socket() {
    // Close the monitor socket if it is open
    if (monitorSocketfd != -1) {
        close(monitorSocketfd);
    }
}

// Getter for the port number
int Socket::getPort() {
    return port;
}

// Setter for the port number
void Socket::setPort(int port) {
    this->port = port; // Assign the given port to the class member
}

// Getter for the monitor socket file descriptor
int Socket::getMonitorSocketfd() {
    return this->monitorSocketfd;
}

// Getter for the client information structure
struct sockaddr_in Socket::getClientInfo() {
    return clientInfo;
}

// Setter for the client information structure
void Socket::setClientInfo(struct sockaddr_in clientInfo) {
    this->clientInfo = clientInfo; // Assign the given client information
}

// Getter for the command socket file descriptor
int Socket::getCommandSocketfd() {
    return this->commandSocketfd;
}

// Getter for the server information structure
struct sockaddr_in Socket::getServerInfo() {
    return serverInfo;
}

// Setter for the server information structure
void Socket::setServerInfo(struct sockaddr_in serverInfo) {
    this->serverInfo = serverInfo; // Assign the given server information
}
