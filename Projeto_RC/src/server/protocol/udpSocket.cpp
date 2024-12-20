#include "udpSocket.hpp"

/**
 * @brief Constructor for a new UdpSocket.
 * Initializes a UDP socket, binds it to the specified port, and sets it up for communication.
 * @param port The port number to bind the socket to.
 * @param verbose If true, enables verbose logging.
 */
UdpSocket::UdpSocket(int port, bool verbose) {
    this->verbose = verbose;
    this->port = port;

    // Creates a new file descriptor for the UDP socket
    this->monitorSocketfd = socket(AF_INET, SOCK_DGRAM, 0); 
    this->commandSocketfd = this->monitorSocketfd; // For UDP, the monitor and command sockets are the same.

    if (this->monitorSocketfd < 0) {
        printf("Error creating socket\n");
    }

    // Set server information for binding
    this->serverInfo.sin_port = htons(this->port);

    // Bind the socket to the specified port
    int error = bind(this->monitorSocketfd, (struct sockaddr *)&this->serverInfo, sizeof(this->serverInfo));

    if (error < 0) {
        // Display a specific error message
        perror("Error binding the socket");
        printf("Error binding the socket to port %d. Error code: %d\n", this->port, errno);

        // Handle specific errors
        if (errno == EADDRINUSE) {
            printf("Port %d is already in use.\n", this->port);
        } else if (errno == EACCES) {
            printf("Permission denied to bind to port %d.\n", this->port);
        }

        // Close the socket and terminate if binding fails
        close(this->monitorSocketfd);
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Constructor for a UdpSocket that wraps an existing socket.
 * Useful for scenarios where a socket is already created, and we want to manage it as a UdpSocket.
 * @param port The port number for the socket.
 * @param verbose If true, enables verbose logging.
 * @param socketfd The file descriptor of the existing socket.
 * @param serverInfo The server's sockaddr_in structure.
 * @param clientInfo The client's sockaddr_in structure.
 */
UdpSocket::UdpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
    this->verbose = verbose;
    this->port = port;
    this->monitorSocketfd = socketfd;
    this->commandSocketfd = socketfd;
    this->serverInfo = serverInfo;
    this->clientInfo = clientInfo;
}

/**
 * @brief Sends data to the last client that sent a message.
 * Uses the client information stored in `clientInfo`.
 * @param data The string data to send.
 */
void UdpSocket::sendData(string data) {
    // Send the data to the client stored in clientInfo
    int n = sendto(this->commandSocketfd, data.c_str(), data.length(), 0, (struct sockaddr*)&this->clientInfo, sizeof(this->clientInfo));

    if (n < 0) {
        // Handle errors during sending
        printf("Error sending data\n");
    }

    if (this->verbose) {
        printf("[PROTOCOL] Sent data: %s\n", data.c_str());
    }
}

/**
 * @brief Receives data from any client.
 * Stores the client's address information in `clientInfo` for future use (e.g., replying with `sendData`).
 * @return string The data received from the client.
 */
string UdpSocket::receiveData() {
    // Buffer to store the incoming message
    char buffer[MAX_UDP_MESSAGE] = {0}; 

    // Length of the client's address structure
    socklen_t len = sizeof(this->clientInfo);

    // Receive data and store the client's address in clientInfo
    int n = recvfrom(this->monitorSocketfd, buffer, MAX_UDP_MESSAGE, 0, (struct sockaddr*)&this->clientInfo, &len);
    if (n < 0) {
        return ""; // Return an empty string if an error occurred
    }

    // Convert the buffer to a C++ string
    string data_received = string(buffer);

    // Remove the trailing newline character
    if (!data_received.empty() && data_received.back() == '\n') {
        data_received.pop_back();
    }

    if (this->verbose) {
        printf("[UDP] Received: %s\n", data_received.c_str());
    }

    return data_received;
}
