#ifndef USER_SHOWRECORD_HPP
#define USER_SHOWRECORD_HPP

#include "../command.hpp"

class ShowRecord : public Command {
    public:
        ShowRecord(string auctionId) : Command(UDP, SHOW_RECORD), auctionId(auctionId) {};

        void send() override;

        void receive() override;

        string formatData() override;

    private:
        string auctionId;
};

#endif