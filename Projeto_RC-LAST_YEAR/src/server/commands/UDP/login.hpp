#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__

#include "../command.hpp"

class Login : public Command {
private:
  string uid;
  string password;

public : 
  Login(vector<string> args);
  void execute() override;
};

#endif
