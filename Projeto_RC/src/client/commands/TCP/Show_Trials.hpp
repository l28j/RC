#ifndef SHOW_TRIALS_H
#define SHOW_TRIALS_H

#include "../command.hpp"

class Show_Trials : public Command {
    private:
    public:
        Show_Trials() : Command(TCP, SHOW_TRIALS) {}    
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};

#endif

