
#include "Debug.hpp"

int Debug::execute() {
    if(this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_IS_PLAYING).c_str());
        return 0;
    }

    return Command::execute();
}

void Debug::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Debug::formatData() {
    return string(DBG) + " " + this->ID + " " + this->game_time + " " + this->content + "\n";
}

void Debug::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RDB || arguments.size() != 1) {
        throw ServerResponseError();
    }

    string status = arguments[0];   

    if (status == OK) {
        this->client->setID(this->ID);
        this->client->setGameTime(this->game_time);
        printf("%s\n", string(GAME_START).c_str());
    }
    else if (status == NOK) {
        printf("%s\n", string(ONGOING_GAME).c_str());
    }
    else if (status == ERR) {
        printf("%s\n", string(INVALID_COMMAND_DEBUG).c_str());
        printf("%s\n", string(AVAILABLE_COLORS).c_str());
    }
    else {
        throw ServerResponseError();
    }
}

