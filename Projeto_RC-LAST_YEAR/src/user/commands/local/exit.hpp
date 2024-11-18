#ifndef USER_EXIT_H
#define USER_EXIT_H

#include "../command.hpp"

using namespace std;

class Exit : public Command {
    public:
        Exit() : Command(EXIT) {};

        int execute() override;

        void send() override;
        void receive() override;

        string formatData() override;
};

#endif
