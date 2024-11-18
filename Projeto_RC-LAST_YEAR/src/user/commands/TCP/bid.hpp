#ifndef CLIENT_BID_H
#define CLIENT_BID_H

#include "../command.hpp"

class Bid : public Command {
    public:
        Bid(string auctionId, string value): 
            Command(TCP, BID), auctionId(auctionId), value(value) 
        {};

        int execute() override;

        void send();
        void receive();
        string formatData();

    private:
        string auctionId;
        string value;
};

#endif