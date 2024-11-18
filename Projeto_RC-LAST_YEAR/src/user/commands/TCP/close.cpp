#include "close.hpp"

int Close::execute() {
    // check if user is logged in
    if(!this->clientState->isLoggedIn()) {
        printf("%s\n", string(NOT_LOGGED_IN).c_str());
        return 0;
    }
    
    return Command::execute();
}

void Close::send() {
    string data = this->formatData();

    this->networkClient->sendData(data);
}

void Close::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != TCP_CLOSE_RESPONSE || args.size() != 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK) {
        printf("%s\n", string(CLOSE_SUCCESS).c_str());
    }
    else if(status == STATUS_NOK) {
        printf("%s\n", string(CLOSE_FAILURE).c_str());
    }
    else if(status == STATUS_NOT_LOGGED_IN) {
        printf("%s\n", string(CLOSE_NOT_LOGGED_IN).c_str());
    }
    else if(status == STATUS_NOT_FOUND) {
        printf("%s\n", string(CLOSE_AUCTION_NOT_FOUND).c_str());
    }
    else if(status == STATUS_NOT_OWNED) {
        printf("%s\n", string(CLOSE_AUCTION_NOT_OWNED).c_str());
    }
    else if(status == STATUS_ALREADY_CLOSED) {
        printf("%s\n", string(CLOSE_ALREADY_CLOSED).c_str());
    }
    else {
        throw ServerResponseError();
    }
}

string Close::formatData() {
    string user = this->clientState->getUser();
    string password = this->clientState->getPassword();
    string data = string(TCP_CLOSE_COMMAND) + " " + user + " " + password + " " + this->auctionId + "\n";

    return data;
}