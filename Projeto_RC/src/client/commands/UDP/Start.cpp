#include "Start.hpp"

int Start::execute() {
    
    if (this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_IS_PLAYING).c_str());
        return 0;
    }

    return Command::execute();
}

void Start::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Start::formatData() {
    return string(SNG) + " " + this->ID + " " + this->game_time + "\n";
}

void Start::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData();
    } catch (const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return;
    }

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RSG || arguments.size() != 1) {
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
    else {
        throw ServerResponseError();
    }    
}



