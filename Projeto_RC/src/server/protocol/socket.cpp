#include "socket.hpp"

// deconstructor for Socket class
Socket::~Socket() {
  if (monitorSocketfd != -1) {
    close(monitorSocketfd);
  }
}

// getter for port
int Socket::getPort() {
  return port;
}

// setter for port
void Socket::setPort(int port) {
  this->port = port;
}

// getter for monitor socketfd
int Socket::getMonitorSocketfd() {
  return this->monitorSocketfd;
}

// getter for command socketfd
int Socket::getCommandSocketfd() {
  return this->commandSocketfd;
}

// getter for serverInfo
struct sockaddr_in Socket::getServerInfo() {
  return serverInfo;
}

// setter for serverInfo
void Socket::setServerInfo(struct sockaddr_in serverInfo) {
  this->serverInfo = serverInfo;
}

// getter for clientInfo
struct sockaddr_in Socket::getClientInfo() {
  return clientInfo;
}

// setter for clientInfo
void Socket::setClientInfo(struct sockaddr_in clientInfo) {
  this->clientInfo = clientInfo;
}

// constructor for Socket class
Socket::Socket() {
  // initialize serverInfo
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
}