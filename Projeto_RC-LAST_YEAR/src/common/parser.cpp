#include "common.hpp"

#include <sstream>

using namespace std;

/**
 * Class used to parse strings using spaces as delimiters
 * - command is the first word of the string
 * - args is a vector of all words except the first
 */
Parser::Parser(string input) {
    this->input = input;

    stringstream ss(input);

    vector<string> tokens;

    string s;

    int i = 0;

    while(getline(ss, s, ' ')) {
        if(i == 0) {
            this->command = s;
        } else {
            this->args.push_back(s);
        }

        i++;
    }

}

// returns first word of input
string Parser::getCommand() {
    return this->command;
}

// returns all words of input except the first in a vector
vector<string> Parser::getArgs() {
    return this->args;
}

string Parser::getInput() {
    return this->input;
}

/**
 * Handles command of type [status, id, isOpen, id, isOpen, ...]
 * @return vector<Auction> 
 */
vector<IAuction> Parser::parseAuctions() {
    vector<IAuction> auctions;

    int auctionsCount = this->args.size() / 2;

    /**
     * i starts at 1 because the first argument is the status
     * to get id you need to do i * 2 - 1 (1, 3, 5, 7, ...)
     * to get isOpen you need to do i * 2 (2, 4, 6, 8, ...)
    */
    
    for(int i = 1; i <= auctionsCount; i++) {
        IAuction auction;

        auction.id = this->args[i * 2 - 1];
        auction.isOpen = stoi(this->args[i * 2]);

        auctions.push_back(auction);
    }
    
    return auctions;
}


/**
 * Handles response to command ShowRecord (sr)
 * @return IShowRecord 
 */
IShowRecord Parser::parseShowRecord() {
    /**
     * string has this format:
    * [host_UID  auction_name  asset_fname start_value start_date-time  timeactive]  
    * [ B bidder_UID bid_value bid_date-time bid_sec_time]*  
    * [ E end_date-time end_sec_time]
     */

    IShowRecord showRecord;

    showRecord.hostId = this->args[1];
    showRecord.auctionName = this->args[2];
    showRecord.assetFrame = this->args[3];
    showRecord.startValue = this->args[4];
    showRecord.startDate = this->args[5];
    showRecord.startTime = this->args[6];
    showRecord.timeActive = this->args[7];

    // Auction has no bids and has not ended
    int index = 8;

    if(this->args.size() == 8) {
        return showRecord;
    }

    while(this->args[index] == "B") {
        IBid bid;

        bid.bidderId = this->args[index + 1];
        bid.value = this->args[index + 2];
        bid.date = this->args[index + 3];
        bid.time = this->args[index + 4];
        bid.timeSinceStart = this->args[index + 5];

        showRecord.bids.push_back(bid);

        index += 6;
    }

    if(this->args[index] == "E") {
        IEnd end;

        end.date = this->args[index + 1];
        end.time = this->args[index + 2];
        end.duration = this->args[index + 3];

        showRecord.end = end;
    }

    return showRecord;
}