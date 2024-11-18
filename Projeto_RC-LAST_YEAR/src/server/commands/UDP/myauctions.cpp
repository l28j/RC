#include "myauctions.hpp"

MyAuctions::MyAuctions(vector<string> args){
  // sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_MY_AUCTIONS;

  // parses the arguments
  this->uid = args[0];

  if (!Verify::isUID(this->uid)) {
    printf("Invalid user\n");
    throw exception();
  }
}

void MyAuctions::execute() {
  // The user is not logged in
  if (!userIsLoggedIn(this->uid)) {
    return this->send(STATUS_NLG);
  }

  // Get the auctions
  string auctions = getUserAuctions(this->uid);

  // The user has not started any auctions
  if (auctions.empty()) {
    return this->send(STATUS_NOK);
  }

  // The user has started some auctions
  return this->send(STATUS_OK + auctions);
}
