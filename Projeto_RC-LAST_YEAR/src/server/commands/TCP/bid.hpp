#ifndef __BID_HPP__
#define __BID_HPP__

#include "../command.hpp"

class Bid : public Command
{
private:
  string uid;
  string password;
  string aid;
  string value;
  
public:
  Bid(vector<string> args);
  void execute() override;
};

#endif
