#ifndef TCP_SOCKET_HPP
#define TCP_SOCKET_HPP

#include "socket.hpp"

class TcpSocket : public Socket{
public:
  TcpSocket(int port, bool verbose);
  TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);

  string receiveData() override;
  void sendData(string data) override;
};

#endif