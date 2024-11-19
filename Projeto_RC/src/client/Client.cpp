#include "Client.hpp"

using namespace std;

bool Client::isPlaying(){
    return !(this->game_time.empty() || this->ID.empty());
}

string Client::getGameTime(){
    return this->game_time;
}

void Client::setGameTime(string game_time){
    this->game_time = game_time ;
}

string Client::getID(){
    return this->ID;
}

void Client::setID(string ID){
    this->ID = ID ;
}