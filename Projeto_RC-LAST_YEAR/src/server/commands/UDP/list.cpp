#include "list.hpp"

List::List(vector<string> args){
  // sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_LIST_AUCTIONS;

  (void) args; // silence unused parameter warning
}

void List::execute() {
  // Get all the auctions
  string auctions = getAllAuctions();

  // If there are no auctions, return NOK
  if (auctions.empty()) {
    return this->send(STATUS_NOK);
  }

  // Return the auctions
  return this->send(STATUS_OK + auctions);
}