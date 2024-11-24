#include "show_trials.hpp"

void ShowTrials::send(){
    string data = formatData();

    this->networkClient->sendData(data);
}


string ShowTrials::formatData() {
    return string(SHOW_TRIALS) + " " + this->id + "\n";
}

void ShowTrials::receive(){}

void ShowTrials::saveFile(string fileName, vector<string>* fileData) {}


