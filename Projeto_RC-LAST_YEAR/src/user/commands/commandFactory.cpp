#include "commandFactory.hpp"

Command* CommandFactory::createCommand(string command, vector<string> arguments) {
    if (command == LOGIN) {
        return CommandFactory::createLogin(arguments);
    } 
    else if (command == LOGOUT) {
        return CommandFactory::createLogout(arguments);
    } 
    else if (command == EXIT) {
        return CommandFactory::createExit(arguments);
    }
    else if(command == UNREGISTER){
        return CommandFactory::createUnregister(arguments);
    }
    else if(command == MY_AUCTIONS || command == MY_AUCTIONS_SHORT){
        return CommandFactory::createMyAuctions(arguments);
    }
    else if(command == MY_BIDS || command == MY_BIDS_SHORT){
        return CommandFactory::createMyBids(arguments);
    }
    else if(command == LIST || command == LIST_SHORT){
        return CommandFactory::createList(arguments);
    }
    else if(command == SHOW_RECORD || command == SHOW_RECORD_SHORT){
        return CommandFactory::createShowRecord(arguments);
    }
    else if(command == SHOW_ASSET || command == SHOW_ASSET_SHORT){
        return CommandFactory::createShowAsset(arguments);
    }
    else if(command == OPEN){
        return CommandFactory::createOpen(arguments);
    }
    else if(command == CLOSE){
        return CommandFactory::createClose(arguments);
    }
    else if(command == BID || command == BID_SHORT){
        return CommandFactory::createBid(arguments);
    }
    else {
        printf("Invalid command\n");
        return nullptr;
    }
}

Command* CommandFactory::createLogin(vector<string> arguments) {
    if(arguments.size() != 2) {
        printf("Usage: login <uid> <password>\n");
        return nullptr;
    }

    string user = arguments[0];
    string password = arguments[1];

    if(!Verify::isUID(user)) {
        printf("%s\n", string(INVALID_UID).c_str());
        return nullptr;
    }

    if(!Verify::isPassword(password)) {
        printf("%s\n", string(INVALID_PASSWORD).c_str());
        return nullptr;
    }

    return new Login(user, password);
}

Command* CommandFactory::createLogout(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: logout\n");
        return nullptr;
    }

    return new Logout();
}

Command* CommandFactory::createExit(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: exit\n");
        return nullptr;
    }

    return new Exit();
}

Command* CommandFactory::createUnregister(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: unregister\n");
        return nullptr;
    }

    return new Unregister();
}

Command* CommandFactory::createMyAuctions(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: myauctions\n");
        return nullptr;
    }

    return new MyAuctions();
}

Command* CommandFactory::createMyBids(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: mybids\n");
        return nullptr;
    }

    return new MyBids();
}

Command* CommandFactory::createList(vector<string> arguments) {
    if(arguments.size() != 0) {
        printf("Usage: list\n");
        return nullptr;
    }

    return new List();
}

Command* CommandFactory::createShowRecord(vector<string> arguments) {
    if(arguments.size() != 1) {
        printf("Usage: showrecord <aid>\n");
        return nullptr;
    }

    string auctionId = arguments[0];

    if(!Verify::isAID(auctionId)) {
        printf("%s\n", string(INVALID_AID).c_str());
        return nullptr;
    }

    /**
     * if user types 1 add rest of characters to be 3 characters long
     */

    if(auctionId.size() == 1) {
        auctionId = "00" + auctionId;
    }
    else if(auctionId.size() == 2) {
        auctionId = "0" + auctionId;
    }

    return new ShowRecord(auctionId);
}

Command* CommandFactory::createShowAsset(vector<string> arguments) {
    if(arguments.size() != 1) {
        printf("Usage: show_asset <aid>\n");
        return nullptr;
    }

    string assetId = arguments[0];

    /**
     * if user types 1 add rest of characters to be 3 characters long
     */

    if(assetId.size() == 1) {
        assetId = "00" + assetId;
    }
    else if(assetId.size() == 2) {
        assetId = "0" + assetId;
    }

    return new ShowAsset(assetId);
}

Command* CommandFactory::createOpen(vector<string> arguments) {
    if(arguments.size() != 4) {
        printf("Usage: open <name> <asset_fname> <start_value> <timeactive>\n");
        return nullptr;
    }

    string name = arguments[0];
    string assetFileName = arguments[1];
    string startValue = arguments[2];
    string timeactive = arguments[3];

    if(!Verify::isAuctionName(name)) {
        printf("%s\n", string(INVALID_AUCTION_NAME).c_str());
        return nullptr;
    }

    if(!Verify::isAuctionStartValue(startValue)) {
        printf("%s\n", string(INVALID_AUCTION_START_VALUE).c_str());
        return nullptr;
    }

    if(!Verify::isAuctionDuration(timeactive)) {
        printf("%s\n", string(INVALID_AUCTION_DURATION).c_str());
        return nullptr;
    }

    if(!Verify::isFileName(assetFileName)) {
        printf("%s\n", string(INVALID_AUCTION_FILE_NAME).c_str());
        return nullptr;
    }

    return new Open(name, startValue, timeactive, assetFileName);
}

Command* CommandFactory::createClose(vector<string> arguments) {
    if(arguments.size() != 1) {
        printf("Usage: close <aid>\n");
        return nullptr;
    }

    string auctionId = arguments[0];

    if(!Verify::isAID(auctionId)) {
        printf("%s\n", string(INVALID_AID).c_str());
        return nullptr;
    }

    /**
     * if user types 1 add rest of characters to be 3 characters long
     */

    if(auctionId.size() == 1) {
        auctionId = "00" + auctionId;
    }
    else if(auctionId.size() == 2) {
        auctionId = "0" + auctionId;
    }

    return new Close(auctionId);
}

Command* CommandFactory::createBid(vector<string> arguments) {
    if(arguments.size() != 2) {
        printf("Usage: bid <aid> <value>\n");
        return nullptr;
    }

    string auctionId = arguments[0];
    string value = arguments[1];

    if(!Verify::isAID(auctionId)) {
        printf("%s\n", string(INVALID_AID).c_str());
        return nullptr;
    }

    if(!Verify::isNumber(value)) {
        printf("%s\n", string(INVALID_VALUE).c_str());
        return nullptr;
    }

    /**
     * if user types 1 add rest of characters to be 3 characters long
     */

    if(auctionId.size() == 1) {
        auctionId = "00" + auctionId;
    }
    else if(auctionId.size() == 2) {
        auctionId = "0" + auctionId;
    }

    return new Bid(auctionId, value);
}