#include "udpSocket.hpp"

// constructor for a new UdpSocket
UdpSocket::UdpSocket(int port, bool verbose) {
  this->port = port;
  this->verbose = verbose;

  this->monitorSocketfd = socket(AF_INET, SOCK_DGRAM, 0); //creates a new file descriptor for the socket
  this->commandSocketfd = this->monitorSocketfd; //for UDP, the command socket is the same as the monitor socket
  
  if (this->monitorSocketfd < 0) {
    printf("Error creating socket\n");
  }
  
  this->serverInfo.sin_port = htons(this->port);

  // bind socket to port
  int err = bind(this->monitorSocketfd, (struct sockaddr *)&this->serverInfo, sizeof(this->serverInfo));

  if (err < 0) {
    // TODO error handling
    printf("Error binding socket to port %d\n", this->port);
  }
}

// constructor for a UdpSocket that already exists
UdpSocket::UdpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo) {
  this->port = port;
  this->verbose = verbose;
  this->monitorSocketfd = socketfd;
  this->commandSocketfd = socketfd;
  this->serverInfo = serverInfo;
  this->clientInfo = clientInfo;
}

string UdpSocket::receiveData() {
  char buffer[CHUNCKS] = {0}; //reset buffer

  socklen_t len = sizeof(this->clientInfo);

  // when we use recvfrom we get the address of the client that sent the data and store it into clientInfo
  int n = recvfrom(this->monitorSocketfd, buffer, CHUNCKS, 0, (struct sockaddr*) &this->clientInfo, &len);
  if (n < 0) {
    return "";
  }

  //convert to our loved c++ strings
  string dataReceived = string(buffer);

  // remove the \n
  dataReceived.pop_back();

  if(this->verbose){
    printf("[UDP] Received: %s\n", dataReceived.c_str());
  }

  return dataReceived;
}

void UdpSocket::sendData(string data) {

  int n = sendto(this->commandSocketfd, data.c_str(), data.length(), 0, (struct sockaddr*) &this->clientInfo, sizeof(this->clientInfo));

  if (n < 0) {
    // TODO error handling
    printf("Error sending data\n");
  }

  if (this->verbose){
    printf("[PROTOCOL] Sent data: %s\n", data.c_str());
  }
}