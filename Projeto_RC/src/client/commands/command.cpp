#include "command.hpp"

using namespace std;

// Sets the client associated with the command.
void Command::setClient(Client *client) {
    this->client = client;
}

// Configures the network client (UDP or TCP) based on the network type.
void Command::setNetworkClient(string serverIp, int serverPort) {
    int networkType = this->networkType;

    if(networkType == UDP) {
        this->networkClient = make_unique<UdpClient>(serverIp, serverPort); // Initialize UDP client.
    }
    else if(networkType == TCP) {
        this->networkClient = make_unique<TcpClient>(serverIp, serverPort); // Initialize TCP client.
    }
}

/**
 * Executes the command: sends data and processes the response.
 * @return int - 0 to continue, 1 to exit.
 */
int Command::execute() {
    this->send();    // Send the command to the server.
    this->receive(); // Receive and handle the server's response.

    return 0;
}

// Retrieves the command string.
string Command::getCommand() {
    return this->command;
}
