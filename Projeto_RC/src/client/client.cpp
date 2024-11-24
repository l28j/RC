#include "client.hpp"

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

void Client::setTrials(string trials){
    this->trials = trials;
}

string Client::getTrials(){
    return this->trials;
}

bool Client::isWin(){
    return this->win;
}

void Client::setWin(bool win){
    this->win = win;
}

bool Client::isLose(){
    return this->lose;
}

void Client::setLose(bool lose){
    this->lose = lose;
}


