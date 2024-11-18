#include "login.hpp"

int Login::execute() {
    if(this->clientState->isLoggedIn()) {
        printf("%s\n", string(USER_ALREADY_LOGGED_IN).c_str());
        return 0;
    }

    return Command::execute();
}

void Login::send() {
    string dataToSend = this->formatData();

    this->networkClient->sendData(dataToSend);
}

void Login::receive() {
    string dataReceived = this->networkClient->receiveData();

    Parser parser = Parser(dataReceived);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != UDP_LOGIN_RESPONSE || args.size() != 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK) {
        this->clientState->loginUser(this->user, this->password);
        printf("%s\n", string(LOGIN_SUCCESS).c_str());
    }

    else if(status == STATUS_NOK) {
        printf("%s\n", string(LOGIN_FAILURE).c_str());
    }
    
    else if(status == STATUS_REGISTERD) {
      this->clientState->loginUser(this->user, this->password);
      printf("%s\n", string(LOGIN_REGISTER).c_str());
    }
    
    else {
        throw ServerResponseError();
    }
}

// returns LIN <user> <password>\n
string Login::formatData() {
    return string(UDP_LOGIN_COMMAND) + " " + this->user + " " + this->password + "\n";
};