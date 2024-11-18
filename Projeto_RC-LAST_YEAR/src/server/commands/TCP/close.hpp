#ifndef __CLOSE_HPP__
#define __CLOSE_HPP__

#include "../command.hpp"

class Close : public Command
{
private:
  string uid;
  string password;
  string aid;

public:
  Close(vector<string> args);
  void execute() override;
};

#endif
