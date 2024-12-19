
#include "Exit.hpp"


int Exit::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(EXITING).c_str());
        return 1;
    }
    int i = Command::execute();
    if (i != 0) {
        std::cerr << "Erro ao executar comando!" << std::endl;
        return i;
    }
    return 1;
}

void Exit::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Exit::formatData() {
    return string(QUT) + " " + this->client->getID() + "\n";
}


void  Exit::receive() {
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


    if (command == ERR || command != RQT || (arguments.size() != 1 && arguments.size() != 5)) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];   

    if (status == OK) {
        this->client->setID("");
        this->client->setGameTime("");
        this->client->setTrials("0");
        this->client->setWin(false);
        this->client->setLose(false);
        printf("%s\n", string(GAME_OVER).c_str());
        printf("%s\n", string(EXITING).c_str());
        printf("Secret code: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
    }
    else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
    }
    else {
        throw ServerResponseError();
    }
}