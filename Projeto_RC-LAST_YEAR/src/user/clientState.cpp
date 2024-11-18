#include "clientState.hpp"

using namespace std;

void ClientState::loginUser(string user, string password) {
    this->setUser(user);
    this->setPassword(password);
}

void ClientState::logoutUser() {
    this->setUser("");
    this->setPassword("");
}

string ClientState::getUser() {
    return this->user;
}

void ClientState::setUser(string user) {
    this->user = user;
}

string ClientState::getPassword() {
    return this->password;
}

void ClientState::setPassword(string password) {
    this->password = password;
}

// Checks if user is logged in by checking if user and password are not empty
bool ClientState::isLoggedIn() {
    return !(this->user.empty() && this->password.empty());
}