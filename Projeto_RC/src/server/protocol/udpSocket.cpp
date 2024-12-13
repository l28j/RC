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
    char buffer[MAX_MESSAGE_SIZE] = {0}; // Inicializa o buffer com zeros

    socklen_t len = sizeof(this->clientInfo);

    // Recebe os dados e armazena o número de bytes recebidos
    int n = recvfrom(this->monitorSocketfd, buffer, MAX_MESSAGE_SIZE, 0, (struct sockaddr*)&this->clientInfo, &len);
    if (n < 0) {
        return ""; // Retorna uma string vazia em caso de erro
    }

    // Cria uma string apenas com os bytes recebidos
    string dataReceived(buffer, n);

    // Remove o caractere '\n' do final da string, se presente
    if (!dataReceived.empty() && dataReceived.back() == '\n') {
        dataReceived.pop_back();
    }

    if (this->verbose) {
        printf("[UDP] Received: %s\n", dataReceived.c_str());
    }

    return dataReceived;
}


void UdpSocket::sendData(string data) {

  int n = sendto(this->commandSocketfd, data.c_str(), data.length(), 0, (struct sockaddr*) &this->clientInfo, sizeof(this->clientInfo));

  if (n < 0) {
    printf("Error sending data\n");
  }

  if (this->verbose){
    printf("[PROTOCOL] Sent data: %s\n", data.c_str());
  }
}