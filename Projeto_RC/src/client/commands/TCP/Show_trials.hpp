#ifndef CLIENT_SHOW_TRIALS_H
#define CLIENT_SHOW_TRIALS_H

#include "../command.hpp"

class ShowTrials : public Command {
    public:
        ShowTrials(string id): Command(TCP, SHOW_TRIALS), id(id) {};
        void send();
        void receive();
        string formatData();

        void saveFile(string fileName, vector<string>* fileData);

    private:
        string id;
};

#endif