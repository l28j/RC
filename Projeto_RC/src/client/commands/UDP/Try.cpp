#include "Try.hpp"

int Try::execute() {
    
    if (!this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
        return 0;
    }

    return Command::execute();
}

void Try::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Try::formatData() {
    if (!this->client->isWin() ) {
        this->client->setTrials(to_string(stoi(this->client->getTrials()) + 1));
        return string(TRY_) + " " + this->ID + " " + this->content + " " + this->nT + "\n";
    }
    else {
        return string(TRY_) + " " + this->ID + " " + this->content + " " + this->nT + "\n";
    }
}

void Try::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RTR ) {
        throw ServerResponseError();
    }

    string status = arguments[0];   

    if (status == OK) {
        if (arguments.size() != 4) {
            throw ServerResponseError();
        }
        else if (arguments[2]=="4") {
            printf("%s\n", string(WIN).c_str());
            this->client->setWin(true);
            
        }
        else {
            printf("Try nº: %s\n", arguments[1].c_str());
            printf("Right: %s\n", arguments[2].c_str());
            printf("Wrong: %s\n", arguments[3].c_str());
        }
    }
    else if (status == DUP){
        printf("%s\n", string(DUPLICATE).c_str());
        this -> client -> setTrials(to_string(stoi(this->client->getTrials()) - 1));
    }
    else if (status == INV){
        printf("%s\n", string(INVALID).c_str());
    }
    else if(status == ENT){
        if (arguments.size() != 5) {
            throw ServerResponseError();
        }
        else {
            printf("%s\n", string(GAME_OVER).c_str());
            printf("Secret: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
            this->client->setLose(true);
        }
    }
    else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
    }
    else if (status == INV) {
        printf("%s\n", string(INVALID).c_str());
    }
    else if(status == ETM){
        printf("%s\n", string(TIME_IS_OVER).c_str());
        printf("Secret: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
        this->client->setLose(true);
    }
    else if(status == ERR){
        printf("%s\n", string(INVALID_COMMAND_TRY).c_str());
        printf("%s\n", string(AVAILABLE_COLORS).c_str());
    }
    else {
        throw ServerResponseError();
    }
}


        
    
    