#ifndef USER_UDP_CLIENT_H
#define USER_UDP_CLIENT_H

#include "networkClient.hpp"

using namespace std;

// UDP client class derived from NetworkClient
class UdpClient : public NetworkClient {
    public:
        UdpClient(string ip, int port);
        int sendData(const string& data);
        string receiveData();

    private:
        int type = UDP;
        bool verbose = UDP_VERBOSE;
};

#endif