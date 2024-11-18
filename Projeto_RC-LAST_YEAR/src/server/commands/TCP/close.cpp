#include "close.hpp"

Close::Close(vector<string> args){
  // sets the socket type and return code
  this->socketType = "TCP";
  this->returnCode = RES_CLOSE_AUCTION;

  // parses the arguments
  this->uid = args[0];
  this->password = args[1];
  this->aid = args[2];

  if (!Verify::isUID(this->uid) || !Verify::isPassword(this->password) || !Verify::isAID(this->aid)){
    printf("Invalid arguments\n");
    throw exception();
  }
}

void Close::execute(){
  // User is not registered
  if (!userIsRegistered(this->uid)) {
    return this->send(STATUS_NOK);
  }
  
  // User is not logged in
  if (!userIsLoggedIn(this->uid)) {
    return this->send(STATUS_NLG);
  }

  // Password does not match
  if (!passwordMatches(this->uid, this->password)) {
    return this->send(STATUS_NOK);
  }

  // Auction does not exist
  if (!auctionExists(this->aid)) {
    return this->send(STATUS_EAU);
  }

  // Auction is not owned by user
  if (!isOwnerAuction(this->uid, this->aid)) {
    return this->send(STATUS_EOW);
  }

  // Auction has already finished
  if (auctionIsFinished(this->aid)) {
    return this->send(STATUS_END);
  }

  // Close the auction
  bool success = closeAuction(this->aid);
  
  // Auction could not be closed
  if (!success) {
    return this->send(STATUS_NOK);
  }

  // Auction was successfully closed
  this->send(STATUS_OK);
}