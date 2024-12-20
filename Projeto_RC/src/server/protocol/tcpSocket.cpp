#include "tcpSocket.hpp"

#include <stdexcept>

TcpSocket::TcpSocket(int port, bool verbose) {
  // Initialize socket
  this->port = port;
  this->verbose = verbose;
  this->monitorSocketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->monitorSocketfd < 0) {
    throw runtime_error("Failed to create monitor socket");
  }

  //add socket options to reuse the port
  int opt = 1;
  if (setsockopt(this->monitorSocketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    throw runtime_error("Failed to set socket options");
  }

  // Set server information
  this->serverInfo.sin_port = htons(this->port);

  int err = bind(this->monitorSocketfd, (struct sockaddr *)&this->serverInfo, sizeof(this->serverInfo));

  if (err < 0) {
      // Exibe a mensagem de erro específico
      perror("Erro ao fazer bind do socket");
      printf("Erro ao vincular o socket à porta %d. Código de erro: %d\n", this->port, errno);

      // Opcional: tomar ações específicas com base no erro
      if (errno == EADDRINUSE) {
          printf("A porta %d já está em uso.\n", this->port);
      } else if (errno == EACCES) {
          printf("Permissão negada para vincular à porta %d.\n", this->port);
      }

      // Encerrar ou liberar recursos se necessário
      close(this->monitorSocketfd);
      exit(EXIT_FAILURE);
  }

  // Start listening
  if (listen(this->monitorSocketfd, 5) < 0) {
    throw runtime_error("Failed to listen on socket");
  }
}

// constructor for a TcpSocket that already exists
TcpSocket::TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo){
  this->port = port;
  this->verbose = verbose;
  this->monitorSocketfd = socketfd;
  this->commandSocketfd = socketfd;
  this->serverInfo = serverInfo;
  this->clientInfo = clientInfo;
}


string TcpSocket::receiveData() {
    // Accept a new connection
    socklen_t len = sizeof(this->clientInfo);
    this->commandSocketfd = accept(this->monitorSocketfd, (struct sockaddr*)&this->clientInfo, &len);
    if (this->commandSocketfd < 0) {
        throw runtime_error("Failed to accept connection");
    }

    // Set timeout for read operation
    struct timeval timeout;
    timeout.tv_sec = 0;  // 0 seconds
    timeout.tv_usec = 200000;  // 200000 microseconds is 0.2 seconds
    if (setsockopt(this->commandSocketfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
        throw runtime_error("Failed to set socket options");
    }

    string dataReceived = "";
    char buffer[1] = {0};
    int n = 0;

    // Read data from the client byte by byte
    while ((n = read(this->commandSocketfd, buffer, sizeof(buffer))) > 0) {
        if (dataReceived.size() + n > MAX_TCP_RECIEVE) {
        this->sendData(ERR); // Send error message
        close(this->commandSocketfd);
        throw runtime_error("Received data exceeds allowed limit");
        }

        dataReceived.append(buffer, n);
    }

    // If read timed out, process the data read so far
    if (n < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
        if (!dataReceived.empty()) {
        dataReceived.pop_back(); // Remove the trailing newline
        }

        if (this->verbose) {
        printf("[TCP] Received data: %s\n", dataReceived.c_str());
        }

        return dataReceived;
    }

    // If another error occurred, close the connection and throw an error
    if (n < 0) {
        close(this->commandSocketfd);
        throw runtime_error("Failed to read data");
    }

    return dataReceived;
}


void TcpSocket::sendData(string data) {
  if (send(this->commandSocketfd, data.c_str(), data.length(), 0) < 0) {
    throw runtime_error("Failed to send data");
  }

  if (this->verbose) {
    printf("[PROTOCOL] Sent data: %s\n", data.c_str());
  }
}