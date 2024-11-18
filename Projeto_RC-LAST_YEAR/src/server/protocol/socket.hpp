#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include "../constants.hpp"

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>


using namespace std;

class Socket {
public:
  Socket();
  ~Socket();

  virtual void sendData(string data) = 0;
  virtual string receiveData() = 0;

  int getPort();
  void setPort(int port);

  int getMonitorSocketfd();
  int getCommandSocketfd();

  struct sockaddr_in getServerInfo();
  void setServerInfo(struct sockaddr_in serverInfo);

  struct sockaddr_in getClientInfo();
  void setClientInfo(struct sockaddr_in clientInfo);

protected:
  int port;
  int monitorSocketfd = -1;
  int commandSocketfd = -1;
  bool verbose;
  struct sockaddr_in serverInfo;
  struct sockaddr_in clientInfo;
};

#endif