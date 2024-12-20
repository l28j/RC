#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include "../constants.hpp" // Include application-specific constants

#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept> // For exception handling

using namespace std;

/**
 * @brief Abstract base class representing a generic network socket.
 * Provides common functionality and defines an interface for derived classes.
 */
class Socket {
public:
    /**
     * @brief Constructor to initialize a socket instance.
     */
    Socket();

    /**
     * @brief Destructor to release resources.
     */
    ~Socket();

    /**
     * @brief Gets the port number associated with the socket.
     * @return int The port number.
     */
    int getPort();

    /**
     * @brief Sets the port number for the socket.
     * @param port The port number to be set.
     */
    void setPort(int port);

    /**
     * @brief Sends data through the socket.
     * This method must be implemented by derived classes.
     * @param data The string data to send.
     */
    virtual void sendData(string data) = 0;

    /**
     * @brief Receives data from the socket.
     * This method must be implemented by derived classes.
     * @return string The data received.
     */
    virtual string receiveData() = 0;

    /**
     * @brief Gets the file descriptor for the monitor socket.
     * @return int The monitor socket file descriptor.
     */
    int getMonitorSocketfd();

    /**
     * @brief Gets the file descriptor for the command socket.
     * @return int The command socket file descriptor.
     */
    int getCommandSocketfd();

    /**
     * @brief Gets the server information structure.
     * @return struct sockaddr_in The server information.
     */
    struct sockaddr_in getServerInfo();

    /**
     * @brief Sets the server information structure.
     * @param serverInfo The server information to set.
     */
    void setServerInfo(struct sockaddr_in serverInfo);

    /**
     * @brief Gets the client information structure.
     * @return struct sockaddr_in The client information.
     */
    struct sockaddr_in getClientInfo();

    /**
     * @brief Sets the client information structure.
     * @param clientInfo The client information to set.
     */
    void setClientInfo(struct sockaddr_in clientInfo);

protected:
    bool verbose;                 // Verbosity flag for debug or log messages.
    int port;                     // Port number for the socket.
    int commandSocketfd = -1;     // File descriptor for the command socket.
    int monitorSocketfd = -1;     // File descriptor for the monitor socket.
    struct sockaddr_in clientInfo; // Client information structure.
    struct sockaddr_in serverInfo; // Server information structure.
};

#endif
