#ifndef __TCPSOCKET_HPP__
#define __TCPSOCKET_HPP__

#include "socket.hpp"

/**
 * @brief Class representing a TCP socket, derived from the base Socket class.
 * Provides functionality for TCP-specific socket operations.
 */
class TcpSocket : public Socket {
public:
    /**
     * @brief Constructor to create and initialize a new TCP socket.
     * @param port The port number to bind the socket to.
     * @param verbose If true, enables verbose logging.
     */
    TcpSocket(int port, bool verbose);

    /**
     * @brief Constructor to wrap an existing TCP socket connection.
     * @param port The port number for the connection.
     * @param verbose If true, enables verbose logging.
     * @param socketfd The file descriptor of the existing socket.
     * @param serverInfo The server's sockaddr_in information.
     * @param clientInfo The client's sockaddr_in information.
     */
    TcpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);

    /**
     * @brief Sends data over the TCP socket.
     * Overrides the base class's pure virtual function.
     * @param data The string data to send.
     */
    void sendData(string data) override;

    /**
     * @brief Receives data from the TCP socket.
     * Overrides the base class's pure virtual function.
     * @return string The data received from the socket.
     */
    string receiveData() override;
};

#endif
