#ifndef __MYBIDS_HPP__
#define __MYBIDS_HPP__

#include "../command.hpp"

class MyBids : public Command
{
private:
  string uid;

public:
  MyBids(vector<string> args);
  void execute() override;
};

#endif
