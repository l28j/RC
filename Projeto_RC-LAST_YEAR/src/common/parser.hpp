#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H

#include <string>
#include <vector>

using namespace std;

struct IAuction {
    string id;
    int isOpen;
};

struct IBid {
    string bidderId;
    string value;
    string date;
    string time;

    string timeSinceStart; // seconds from start of auction until this bid
};

struct IEnd {
    string date;
    string time;
    string duration; // duration of auction in seconds
};

struct IShowRecord {
    string hostId;
    string auctionName;
    string assetFrame;
    string startValue;
    string startDate;
    string startTime;
    string timeActive; // seconds from start of auction until now

    // last 50 bids, from lowest value to highest
    vector<IBid> bids; 

    // auction end date, time and duration
    IEnd end;

    bool hasBids() {
        return this->bids.size() > 0;
    }

    // returns last bid or empty bid if there are no bids
    string lastBid() {
        if(this->hasBids())
            return this->bids[this->bids.size() - 1].value;
        else return "";
    }

    bool hasEnded() {
        return this->end.date != "";
    }
};

class Parser {
    public:
        Parser(string input);
        string getCommand();
        vector<string> getArgs();
        string getInput();

        vector<IAuction> parseAuctions();

        IShowRecord parseShowRecord();

    private:
        string input;
        string command;
        vector<string> args;
};

#endif