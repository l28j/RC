#ifndef CLIENT_CLOSE_H
#define CLIENT_CLOSE_H

#include "../command.hpp"

class Close : public Command {
    public:
        Close(string auctionId): Command(TCP, CLOSE), auctionId(auctionId) {};

        int execute() override;

        void send();
        void receive();
        string formatData();

    private:
        string auctionId;
};

#endif