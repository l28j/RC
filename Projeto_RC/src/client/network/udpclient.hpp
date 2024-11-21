#ifndef USER_UDP_CLIENT_H
#define USER_UDP_CLIENT_H

#include "networkclient.hpp"

using namespace std;

// UDP client class derived from NetworkClient
class UdpClient : public NetworkClient {
    public:
        UdpClient(string ip, int port);
        int sendData(const string& data);
        string receiveData();

    private:
        int type = UDP;
};

#endif