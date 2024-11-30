#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

#include "socket.hpp"

class UdpSocket : public Socket {
public:
  UdpSocket(int port, bool verbose);
  UdpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);

  string receiveData() override;
  void sendData(string data) override;
};

#endif