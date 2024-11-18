#include "networkClient.hpp"

NetworkClient::~NetworkClient(){
    if(this->sockfd >= 0){
        close(this->sockfd);
    }
}