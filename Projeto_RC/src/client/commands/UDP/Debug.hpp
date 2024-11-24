#ifndef DEBUG_H
#define DEBUG_H


#include "../command.hpp"


class Debug : public Command {
    private:
        string ID;
        string game_time;
        string content;
    public:
        Debug(string ID , string game_time, string content) : Command(UDP, START), ID(ID), game_time(game_time), content(content) {}    
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};



#endif