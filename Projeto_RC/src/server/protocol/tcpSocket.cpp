#include "tcpSocket.hpp"

#include <stdexcept>

// Constructor: Initializes a new TCP socket for monitoring connections.
TcpSocket::TcpSocket(int port, bool verbose) {
    this->port = port;
    this->verbose = verbose;

    // Create the socket.
    this->monitorSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->monitorSocketfd < 0) {
        throw runtime_error("Failed to create monitor socket");
    }

    // Set socket options to allow port reuse.
    int opt = 1;
    if (setsockopt(this->monitorSocketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw runtime_error("Failed to set socket options");
    }

    // Set server information, including the port.
    this->serverInfo.sin_port = htons(this->port);

    // Bind the socket to the specified port.
    int err = bind(this->monitorSocketfd, (struct sockaddr*)&this->serverInfo, sizeof(this->serverInfo));
    if (err < 0) {
        printf("Error binding socket to port %d\n", this->port); // Error handling for binding failure.
    }

    // Start listening for incoming connections.
    if (listen(this->monitorSocketfd, 5) < 0) {
        throw runtime_error("Failed to listen on socket");
    }
}

// Constructor: Initializes a TCP socket using an existing connection.
TcpSocket::TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
    this->port = port;
    this->verbose = verbose;
    this->monitorSocketfd = socketfd;
    this->commandSocketfd = socketfd;
    this->serverInfo = serverInfo;
    this->clientInfo = clientInfo;
}

// Receives data from a connected client.
string TcpSocket::receiveData() {
    // Accept a new connection.
    socklen_t len = sizeof(this->clientInfo);
    this->commandSocketfd = accept(this->monitorSocketfd, (struct sockaddr*)&this->clientInfo, &len);
    if (this->commandSocketfd < 0) {
        throw runtime_error("Failed to accept connection");
    }

    // Set a timeout for the read operation.
    struct timeval timeout;
    timeout.tv_sec = 0;         // 0 seconds.
    timeout.tv_usec = 200000;   // 200 milliseconds.
    if (setsockopt(this->commandSocketfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
        throw runtime_error("Failed to set socket options");
    }

    string dataReceived = "";
    char buffer[1] = {0};
    int n = 0;

    // Read data from the client byte by byte.
    while ((n = read(this->commandSocketfd, buffer, sizeof(buffer))) > 0) {
        dataReceived.append(buffer, n);
    }

    // Handle timeout or successful read.
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        dataReceived.pop_back(); // Remove the trailing newline character.

        if (this->verbose) {
            printf("[TCP] Received data: %s\n", dataReceived.c_str());
        }

        // Check if the received data exceeds the maximum allowed size.
        if (dataReceived.length() > MAX_TCP_REPLY_SIZE) {
            this->sendData(ERR);
            close(this->commandSocketfd);
        }

        return dataReceived;
    }

    // Handle other errors during reading.
    else if (n < 0) {
        close(this->commandSocketfd);
        throw runtime_error("Failed to read data");
    }

    return dataReceived;
}

// Sends data to the connected client.
void TcpSocket::sendData(string data) {
    if (send(this->commandSocketfd, data.c_str(), data.length(), 0) < 0) {
        throw runtime_error("Failed to send data");
    }

    if (this->verbose) {
        printf("[PROTOCOL] Sent data: %s\n", data.c_str());
    }
}
