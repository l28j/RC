#ifndef SCOREBOARD_H
#define SCOREBOARD_H


#include "../command.hpp"


class Scoreboard : public Command {
    private:
    public:
        Scoreboard() : Command(TCP, SCORE_BOARD) {}    
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};

#endif