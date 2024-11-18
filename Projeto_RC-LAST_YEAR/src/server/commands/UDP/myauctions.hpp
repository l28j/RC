#ifndef __MYAUCTIONS_HPP__
#define __MYAUCTIONS_HPP__

#include "../command.hpp"

class MyAuctions : public Command
{
private:
  string uid;

public:
  MyAuctions(vector<string> args);
  void execute() override;
};

#endif
