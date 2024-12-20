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

// Abstract class representing a generic socket for communication.
class Socket {
public:
  Socket(); // Constructor.
  ~Socket(); 
  
  // Pure virtual methods to be implemented by derived classes.
  virtual void sendData(string data) = 0; // Sends data through the socket.
  virtual string receiveData() = 0; // Receives data from the socket.

  int getPort(); // Retrieves the port number.
  void setPort(int port); // Sets the port number.

  int getMonitorSocketfd(); // Retrieves the monitor socket file descriptor.
  int getCommandSocketfd(); // Retrieves the command socket file descriptor.

  struct sockaddr_in getServerInfo(); // Retrieves server socket information.
  void setServerInfo(struct sockaddr_in serverInfo); // Sets server socket information.

  struct sockaddr_in getClientInfo(); // Retrieves client socket information.
  void setClientInfo(struct sockaddr_in clientInfo); // Sets client socket information.

protected:
  int port; // Port number for the socket.
  int monitorSocketfd = -1; 
  int commandSocketfd = -1;
  bool verbose; // Verbose mode for debugging.
  struct sockaddr_in serverInfo; // Server socket information.
  struct sockaddr_in clientInfo; // Client socket information.
};

#endif
