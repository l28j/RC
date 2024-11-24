#ifndef QUIT_H
#define QUIT_H


#include "../command.hpp"

class Quit : public Command {
    public:
        Quit() : Command(UDP, QUIT) {}
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};


#endif