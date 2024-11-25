
#include "Quit.hpp"

int Quit::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
        return 0;
    }
    
    else {
        int i = Command::execute();
        if (i == 0) {
            printf("%s\n", string(GAME_END).c_str());
            return 1 ;
        }
        else {
            return 0;
    
        }
    }
}

void Quit::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Quit::formatData() {
    return string(QUT) + " " + this->client->getID() + "\n";
}

void Quit::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RQT || arguments.size() != 5) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];   

    if (status == OK) {
        this->client->setID("");
        this->client->setGameTime("");
        this->client->setTrials("0");
        this->client->setWin(false);
        this->client->setLose(false);
        printf("Secret code: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
    }
    else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
    }
    else {
        throw ServerResponseError();
    }
}