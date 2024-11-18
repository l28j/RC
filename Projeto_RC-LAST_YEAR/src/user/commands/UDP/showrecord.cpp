#include "showrecord.hpp"

void ShowRecord::send() {
    string data = formatData();
    
    this->networkClient->sendData(data);
}

void ShowRecord::receive() {
    string data = this->networkClient->receiveData();
    
    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != UDP_SHOW_RECORD_RESPONSE || args.size() < 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK){
        IShowRecord showRecord = parser.parseShowRecord();
        printf("%s started auction at %s %s with initial value of %s\n", showRecord.hostId.c_str(), showRecord.startDate.c_str(), showRecord.startTime.c_str(), showRecord.startValue.c_str());
        printf("Asset frame: %s\n", showRecord.assetFrame.c_str());
        printf("List of the last %lu bids of %s auction\n", showRecord.bids.size(), this->auctionId.c_str());

        for(IBid bid : showRecord.bids) {
            printf("Bidder %s: bid value %s at %s %s\n", bid.bidderId.c_str(), bid.value.c_str(), bid.date.c_str(), bid.time.c_str());
        }

        if(showRecord.hasEnded()) {
            printf("Auction %s ended at %s %s\n", this->auctionId.c_str(), showRecord.end.date.c_str(), showRecord.end.time.c_str());
            printf("Auction %s lasted %s seconds\n", this->auctionId.c_str(), showRecord.end.duration.c_str());

            if(showRecord.hasBids()) {
                string lastBid = showRecord.lastBid();
                printf("Auction %s last bid was %s\n", this->auctionId.c_str(), lastBid.c_str());
            }
        } else {
            printf("Auction %s is still active\n", this->auctionId.c_str());
            printf("Auction %s has max time of %s seconds\n", this->auctionId.c_str(), showRecord.timeActive.c_str());
        
        }
    }
    else if(status == STATUS_NOK){
        printf("Auction %s not found\n", this->auctionId.c_str());
    }
    else {
        throw ServerResponseError();
    }
}

string ShowRecord::formatData() {
    return string(UDP_SHOW_RECORD_COMMAND) + " " + auctionId + "\n";
}