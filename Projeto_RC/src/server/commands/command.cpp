#include "command.hpp"

// Sets up the socket connection based on the specified type (UDP or TCP).
void Command::setupSocketConnection(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
    if (this->socketType == "UDP") {
        this->socket = make_unique<UdpSocket>(port, verbose, socketfd, serverInfo, clientInfo);
    }

    if (this->socketType == "TCP") {
        this->socket = make_unique<TcpSocket>(port, verbose, socketfd, serverInfo, clientInfo);
    }
}

// Sends a response using the configured socket and closes the TCP connection if necessary.
void Command::send(string status) {
    string response = string(this->returnCode) + " " + status + "\n"; // Format the response.

    this->socket->sendData(response); // Send the response.

    if (this->socketType == "TCP") { // Close the unique TCP socket connection.
        close(this->socket->getCommandSocketfd());
    }
}
