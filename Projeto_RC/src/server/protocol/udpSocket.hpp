#ifndef __UDPSOCKET_HPP__
#define __UDPSOCKET_HPP__

#include "socket.hpp"

/**
 * @brief Class representing a UDP socket, derived from the base Socket class.
 * Provides functionality for UDP-specific socket operations.
 */
class UdpSocket : public Socket {
public:
    /**
     * @brief Constructor to create and initialize a new UDP socket.
     * @param port The port number to bind the socket to.
     * @param verbose If true, enables verbose logging.
     */
    UdpSocket(int port, bool verbose);

    /**
     * @brief Constructor to wrap an existing UDP socket.
     * Useful for managing a pre-existing socket with the UdpSocket class.
     * @param port The port number for the socket.
     * @param verbose If true, enables verbose logging.
     * @param socketfd The file descriptor of the existing socket.
     * @param serverInfo The server's sockaddr_in structure.
     * @param clientInfo The client's sockaddr_in structure.
     */
    UdpSocket(int port, bool verbose, int socketfd, struct sockaddr_in serverInfo, struct sockaddr_in clientInfo);

    /**
     * @brief Sends data to the last client that communicated with the socket.
     * Overrides the base class's pure virtual function.
     * @param data The string data to send.
     */
    void sendData(string data) override;

    /**
     * @brief Receives data from any client.
     * Stores the sender's address information for future use.
     * Overrides the base class's pure virtual function.
     * @return string The data received from the client.
     */
    string receiveData() override;
};

#endif
