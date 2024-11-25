#ifndef TRY__H
#define TRY_H

#include "../command.hpp"

class Try : public Command {
    private:
        vector<string> content;
    public:
        Try(vector<string> content) : Command(UDP, TRY), content(content) {}
        int execute() override;
        void send() override;
        void receive() override;
        string formatData();
};

#endif