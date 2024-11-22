#include "try.hpp"

int Try::execute() {
    
    if (this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_IS_PLAYING).c_str());
        return 0;
    }

    return Command::execute();
}

void Try::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Try::formatData() {
    return string(START) + " " + this->ID + " " + this->content + " " + this->nT + "\n";
}