#include "bid.hpp"

int Bid::execute() {
    // check if user is logged in
    if(!this->clientState->isLoggedIn()) {
        printf("%s\n", string(NOT_LOGGED_IN).c_str());
        return 0;
    }
    
    return Command::execute();
}

void Bid::send() {
    string data = this->formatData();

    this->networkClient->sendData(data);
}

void Bid::receive() {
    string data = this->networkClient->receiveData();

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != TCP_BID_RESPONSE || args.size() != 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_NOK) {
        printf("%s\n", string(BID_NOT_ACTIVE).c_str());
    }
    else if(status == STATUS_NOT_LOGGED_IN) {
        printf("%s\n", string(BID_NOT_LOGGED_IN).c_str());
    }
    else if(status == STATUS_ACCEPTED) {
        printf("%s\n", string(BID_ACCEPTED).c_str());
    }
    else if (status == STATUS_REFUSED) {
        printf("%s\n", string(BID_REFUSED).c_str());
    }
    else if (status == STATUS_ILLEGAL) {
        printf("%s\n", string(BID_ILLEGAL).c_str());

    }
    else {
        throw ServerResponseError();
    }

}

string Bid::formatData() {
    string user = this->clientState->getUser();
    string password = this->clientState->getPassword();
    string data = string(TCP_BID_COMMAND) + " " + user + " " + password + " " + this->auctionId + " " + this->value + "\n";

    return data;
}