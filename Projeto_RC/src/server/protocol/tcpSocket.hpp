#ifndef __TCPSOCKET_HPP__
#define __TCPSOCKET_HPP__

#include "socket.hpp"

class TcpSocket : public Socket{
public:
  TcpSocket(int port, bool verbose);
  TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);

  string receiveData() override;
  void sendData(string data) override;
};

#endif