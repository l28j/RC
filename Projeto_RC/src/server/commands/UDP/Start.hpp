#ifndef __START_HPP__
#define __START_HPP__

#include "../command.hpp"

class Start : public Command{

private:
  string PLID;
  string timeStr;

public:
  Start(vector<string> args);
  void execute() override;
};

#endif
