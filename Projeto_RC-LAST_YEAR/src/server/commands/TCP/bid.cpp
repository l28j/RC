#include "bid.hpp"

Bid::Bid(vector<string> args){
  // sets the socket type and return code
  this->socketType = "TCP";
  this->returnCode = RES_PLACE_BID;

  // parses the arguments
  this->uid = args[0];
  this->password = args[1];
  this->aid = args[2];
  this->value = args[3];

  if (!Verify::isAID(this->aid)){
    printf("aid argument is invalid\n");
    throw exception();
  }
}

void Bid::execute(){
  // Auction does not exist
  if (!auctionExists(this->aid)){
    return this->send(STATUS_NOK);
  }

  // Auction is not active
  if (auctionIsFinished(this->aid)){
    return this->send(STATUS_NOK);
  }

  // Auction is owned by the user
  if (isOwnerAuction(this->uid, this->aid)){
    return this->send(STATUS_ILG);
  }

  // If bid is not higher than the current bid
  if (!isHigherBid(this->aid, this->value)){
    return this->send(STATUS_REF);
  }

  // Place bid
  placeBid(this->uid, this->aid, this->value);

  // Return the asset
  return this->send(STATUS_ACC); 
}