#include "unregister.hpp"

Unregister::Unregister(vector<string> args){
  // sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_UNREGISTER;

  // parses the arguments
  this->uid = args[0];
  this->password = args[1];

  if (!Verify::isUID(this->uid) || !Verify::isPassword(this->password)){
    printf("Invalid user or password\n");
    throw exception();
  }
}

void Unregister::execute(){
  if (!userIsRegistered(this->uid)){
    return this->send(STATUS_UNR);
  }

  if (!passwordMatches(this->uid, this->password)){
    return this->send(STATUS_NOK);
  }

  // The user is not logged in
  if (!userIsLoggedIn(this->uid)) {
    return this->send(STATUS_NOK);
  }
  
  // The user is logged in, so log them out and unregister them
  logoutUser(this->uid);
  unregisterUser(this->uid);

  return this->send(STATUS_OK);
}