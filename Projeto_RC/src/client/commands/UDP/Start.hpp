#ifndef START_H
#define START_H

#include "../command.hpp"

class Start : public Command {
    private:
        string ID;
        string game_time;
    public:
        Start(string ID , string game_time) : Command(UDP, START), ID(ID), game_time(game_time) {}
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};

#endif