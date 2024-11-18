#include "login.hpp"

Login::Login(vector<string> args) {
  //sets the socket type and return code
  this->socketType = "UDP";
  this->returnCode = RES_LOGIN;

  //parses the arguments
  this->uid = args[0];
  this->password = args[1];

  if (!Verify::isUID(this->uid) || !Verify::isPassword(this->password)){
    printf("Invalid user or password\n");
    throw exception();
  }
}

void Login::execute(){
  // The user is not registered
  if (!userIsRegistered(this->uid)){
    // Register and log in the user
    registerUser(this->uid, this->password);
    createLoginFile(this->uid);
    return this->send(STATUS_REG);
  }

  // The password is incorrect
  if (!passwordMatches(this->uid, this->password)){
    return this->send(STATUS_NOK);
  }
  
  // Log in the user
  createLoginFile(this->uid);
  return this->send(STATUS_OK);
}