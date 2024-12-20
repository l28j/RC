#include "client.hpp"

using namespace std;

// Checks if the client is currently playing a game.
bool Client::isPlaying() {
    return !(this->game_time.empty() || this->ID.empty());
}

// Gets the game time for the client.
string Client::getGameTime() {
    return this->game_time;
}

// Sets the game time for the client.
void Client::setGameTime(string game_time) {
    this->game_time = game_time;
}

// Gets the client ID.
string Client::getID() {
    return this->ID;
}

// Sets the client ID.
void Client::setID(string ID) {
    this->ID = ID;
}

// Sets the number of trials the client has made.
void Client::setTrials(string trials) {
    this->trials = trials;
}

// Gets the number of trials the client has made.
string Client::getTrials() {
    return this->trials;
}

// Checks if the client has won the game.
bool Client::isWin() {
    return this->win;
}

// Sets the win status for the client.
void Client::setWin(bool win) {
    this->win = win;
}

// Checks if the client has lost the game.
bool Client::isLose() {
    return this->lose;
}

// Sets the lose status for the client.
void Client::setLose(bool lose) {
    this->lose = lose;
}

// Resets the client's game state.
void Client::reset() {
    this->game_time = "";
    this->trials = "0";
    this->win = false;
    this->lose = false;
}
