#ifndef __SHOWRECORD_HPP__
#define __SHOWRECORD_HPP__

#include "../command.hpp"

class ShowRecord : public Command
{
private:
  string aid;

public:
  ShowRecord(vector<string> args);
  void execute() override;
};

#endif
