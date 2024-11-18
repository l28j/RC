#include "command.hpp"

using namespace std;

void Command::setClientState(ClientState *clientState) {
    this->clientState = clientState;
}

void Command::setNetworkClient(string serverIp, int serverPort) {
    int networkType = this->networkType;

    if(networkType == UDP) {
        this->networkClient = make_unique<UdpClient>(serverIp, serverPort);
    }

    else if(networkType == TCP) {
        this->networkClient = make_unique<TcpClient>(serverIp, serverPort);
    }
}

/**
 * Executes the command received from the user
 * @return int - 0 if continue, 1 if exit
 */
int Command::execute() {
    this->send();
    this->receive();

    return 0;
}

string Command::getCommand() {
    return this->command;
}