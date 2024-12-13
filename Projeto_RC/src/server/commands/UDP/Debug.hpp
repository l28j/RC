
#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include "../command.hpp"
#include "../../storage.hpp"
#include <ctime>
#include <iostream>
#include <cstdio>

class Debug : public Command{

private:
  string PLID;
  string timeStr;
  string code;

public:
  Debug(vector<string> args);
  void execute() override;
};

#endif
