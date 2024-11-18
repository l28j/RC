#ifndef USER_MYAUCTIONS_H
#define USER_MYAUCTIONS_H

#include "../command.hpp"

class MyAuctions : public Command {
    public:
        MyAuctions() : Command(UDP, MY_AUCTIONS) {};

        int execute() override;

        void send() override;
        void receive() override;

        string formatData() override;
};

#endif // MYAUCTIONS_H
