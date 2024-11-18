#include "mybids.hpp"

MyBids::MyBids(vector<string> args){
  // sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_MY_BIDS;

  // parses the arguments
  this->uid = args[0];

  if (!Verify::isUID(this->uid)){
    printf("Invalid user\n");
    throw exception();
  }
}

void MyBids::execute() {
  // The user is not logged in
  if (!userIsLoggedIn(this->uid)) {
    return this->send(STATUS_NLG);
  }

  // Get the bids
  string bids = getUserBids(this->uid);

  // The user has not placed any bids
  if (bids.empty()) {
    return this->send(STATUS_NOK);
  }
  
  // The user has placed some bids
  return this->send(STATUS_OK + bids);
}
