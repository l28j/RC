#ifndef __LOGOUT_HPP__
#define __LOGOUT_HPP__

#include "../command.hpp"

class Logout : public Command {
private:
  string uid;
  string password;

public:
  Logout(vector<string> args);
  void execute() override;
};

#endif
