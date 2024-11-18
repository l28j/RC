#ifndef __UNREGISTER_HPP__
#define __UNREGISTER_HPP__

#include "../command.hpp"

class Unregister : public Command{
private:
  string uid;
  string password;

public:
  Unregister(vector<string> args);
  void execute() override;
};

#endif
