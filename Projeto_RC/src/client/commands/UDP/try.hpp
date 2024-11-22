#ifndef TRY__H
#define TRY_H

#include "../command.hpp"

class Try : public Command {
    private:
        string ID;
        string nT;
        string content;
    public:
        Try(string ID , string nT, string content) : Command(UDP, TRY), ID(ID), nT(nT), content(content) {}
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};

#endif