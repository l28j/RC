#include "tcpSocket.hpp"

#include <stdexcept>

/**
 * @brief Constructor for TcpSocket to create and initialize a new socket.
 * @param port The port number to bind the socket to.
 * @param verbose If true, enables verbose logging.
 */
TcpSocket::TcpSocket(int port, bool verbose) {
    // Initialize socket
    this->verbose = verbose;
    this->port = port;
    this->monitorSocketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->monitorSocketfd < 0) {
        throw runtime_error("Failed to create monitor socket");
    }

    // Add socket options to reuse the port
    int option = 1;
    if (setsockopt(this->monitorSocketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &option, sizeof(option))) {
        throw runtime_error("Failed to set socket options");
    }

    // Set server information
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

        // Close the socket and exit
        close(this->monitorSocketfd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(this->monitorSocketfd, 5) < 0) {
        throw runtime_error("Failed to listen on socket");
    }
}

/**
 * @brief Constructor for TcpSocket to wrap an existing socket connection.
 * @param port The port number for the connection.
 * @param verbose If true, enables verbose logging.
 * @param socketfd The file descriptor of the existing socket.
 * @param serverInfo The server's sockaddr_in information.
 * @param clientInfo The client's sockaddr_in information.
 */
TcpSocket::TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
    this->verbose = verbose;
    this->port = port;
    this->serverInfo = serverInfo;
    this->clientInfo = clientInfo;
    this->monitorSocketfd = socketfd;
    this->commandSocketfd = socketfd;
}

/**
 * @brief Sends data to the connected client.
 * @param data The string data to send.
 * @throws runtime_error if sending data fails.
 */
void TcpSocket::sendData(string data) {
    if (send(this->commandSocketfd, data.c_str(), data.length(), 0) < 0) {
        throw runtime_error("Failed to send data");
    }

    if (this->verbose) {
        printf("[PROTOCOL] Sent data: %s\n", data.c_str());
    }
}

/**
 * @brief Receives data from the connected client.
 * @return string The data received from the client.
 * @throws runtime_error if receiving data fails or exceeds the allowed limit.
 */
string TcpSocket::receiveData() {
    // Accept a new connection
    socklen_t size = sizeof(this->clientInfo);
    this->commandSocketfd = accept(this->monitorSocketfd, (struct sockaddr*)&this->clientInfo, &size);
    if (this->commandSocketfd < 0) {
        throw runtime_error("Failed to accept connection");
    }

    // Set timeout for the read operation
    struct timeval time_out;
    time_out.tv_sec = 0;  // 0 seconds
    time_out.tv_usec = 200000;  // 0.2 seconds
    if (setsockopt(this->commandSocketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&time_out, sizeof(time_out)) < 0) {
        throw runtime_error("Failed to set socket options");
    }

    string data_received = "";
    int n = 0;
    char buffer[1] = {0};

    // Read data from the client byte by byte
    while ((n = read(this->commandSocketfd, buffer, sizeof(buffer))) > 0) {
        if (data_received.size() + n > MAX_TCP_RECIEVE) {
            this->sendData(ERR); // Send error message
            close(this->commandSocketfd);
            throw runtime_error("Received data exceeds allowed limit");
        }

        data_received.append(buffer, n);
    }

    // If read timed out, process the data read so far
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        if (!data_received.empty()) {
            data_received.pop_back(); // Remove the trailing newline
        }

        if (this->verbose) {
            printf("[TCP] Received data: %s\n", data_received.c_str());
        }

        return data_received;
    }

    // If another error occurred, close the connection and throw an error
    if (n < 0) {
        close(this->commandSocketfd);
        throw runtime_error("Failed to read data");
    }

    return data_received;
}
