#include "unregister.hpp"

int Unregister::execute() {
    // check if user is logged in
    if(!this->clientState->isLoggedIn()) {
        printf("%s\n", string(NOT_LOGGED_IN).c_str());
        return 0;
    }
    
    return Command::execute();
}

void Unregister::send(){
    string dataToSend = this->formatData();

    this->networkClient->sendData(dataToSend);
}

void Unregister::receive(){
    string dataReceived = this->networkClient->receiveData();

    Parser parser = Parser(dataReceived);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != UDP_UNREGISTER_RESPONSE || args.size() != 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK) {
        this->clientState->logoutUser();

        printf("%s\n", string(UNREGISTER_SUCCESS).c_str());
    }

    else if(status == STATUS_NOK) {
        printf("%s\n", string(UNREGISTER_FAILURE).c_str());
    }

    else if(status == STATUS_UNREGISTERD) {
        printf("%s\n", string(UNREGISTER_UNREGISTER).c_str());
    }
    
    else {
        throw ServerResponseError();
    }
}

// returns UNR <username> <password>\n
string Unregister::formatData() {
    return string(UDP_UNREGISTER_COMMAND) + " " + this->clientState->getUser() + " " + this->clientState->getPassword() + "\n";
}