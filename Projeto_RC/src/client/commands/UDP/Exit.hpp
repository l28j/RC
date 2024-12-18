#ifndef EXIT_H
#define EXIT_H


#include "../command.hpp"

class Exit : public Command {
    public:
        Exit() : Command(UDP, EXIT) {}
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};


#endif