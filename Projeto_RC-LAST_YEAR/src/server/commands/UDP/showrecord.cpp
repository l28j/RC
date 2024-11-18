#include "showrecord.hpp"

ShowRecord::ShowRecord(vector<string> args){
  // sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_SHOW_RECORD;

  // parses the arguments
  this->aid = args[0];

  if (!Verify::isAID(this->aid)){
    printf("Invalid AID\n");
    throw exception();
  }
}

void ShowRecord::execute() {
  // The auction does not exist
  if (!auctionExists(this->aid)) {
    return this->send(STATUS_NOK);
  }

  // Get the auction info
  string auctionInfo = getAuctionInfo(this->aid);

  // Get the bids info
  string bidsInfo = getAuctionBidsInfo(this->aid);

  // Get the end info
  string endInfo = getAuctionEndInfo(this->aid);

  // Send the auction information
  return this->send(STATUS_OK + string(" ") + auctionInfo + bidsInfo + endInfo);
}
