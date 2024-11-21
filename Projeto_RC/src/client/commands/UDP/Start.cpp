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
    return string(START) + " " + this->ID + " " + this->game_time + "\n";
}


