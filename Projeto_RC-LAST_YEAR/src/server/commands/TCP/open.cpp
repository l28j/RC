#include "open.hpp"

Open::Open(vector<string> args){
  // sets the socket type and return code
  this->socketType = "TCP";
  this->returnCode = RES_OPEN_AUCTION;

  // parses the arguments
  this->uid = args[0];
  this->password = args[1];
  this->name = args[2];
  this->startValue = args[3];
  this->timeActive = args[4];
  this->fName = args[5];
  this->fSize = args[6];

  //fData is the concatenation of all the arguments after the 7th with spaces between them
  for (long unsigned int i = 7; i < args.size(); i++){
    this->fData += args[i];
    if (i != args.size() - 1){
      this->fData += " ";
    }
  }

  if (!Verify::isUID(this->uid) || !Verify::isPassword(this->password) || !Verify::isFileName(this->fName) || !Verify::isAuctionDuration(this->timeActive) || !Verify::isAuctionName(this->name) || !Verify::isAuctionStartValue(this->startValue)){
    printf("Invalid arguments\n");
    throw exception();
  }
}

void Open::execute(){
  // User is not logged in
  if (!userIsLoggedIn(this->uid)) {
    return this->send(STATUS_NLG);
  }

  // Password does not match
  if (!passwordMatches(this->uid, this->password)) {
    return this->send(STATUS_NOK);
  }

  // Start a new auction 
  string AID = createAuction(this->uid, this->name, this->startValue, this->timeActive, this->fName, this->fData);

  if (AID == ""){
    return this->send(STATUS_NOK);
  }

  // Send response
  return this->send(STATUS_OK + string(" ") + AID);
}