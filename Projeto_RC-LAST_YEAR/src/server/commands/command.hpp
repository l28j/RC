#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__

#include <string>
#include <stdexcept>

// socket includes
#include "../protocol/socket.hpp"
#include "../protocol/udpSocket.hpp"
#include "../protocol/tcpSocket.hpp"

#include "../../common/verify.hpp"
#include "../database.hpp"

using namespace std;

// Command abstract class
/**
 * 0 is a pure virtual function
 * default tells the compiler to use the default implementation
 */
class Command {
protected:
  unique_ptr<Socket> socket;
  string socketType;
  string returnCode;

public:
  virtual void execute() = 0; //needs to be implemented by the child class

  void send(string status);
  void setupSocketConnection(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);
};

#endif