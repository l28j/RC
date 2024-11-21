#ifndef USER_TCP_CLIENT_H
#define USER_TCP_CLIENT_H

#include "networkclient.hpp"
#include <cstring>
#include <iostream>

#include "../../common/common.hpp"

using namespace std;

// TCP client class derived from NetworkClient
class TcpClient : public NetworkClient {
    public:
        TcpClient(string ip, int port);
        int sendData(const string& data);
        string receiveData();

    private:
        int type = TCP;
};

#endif