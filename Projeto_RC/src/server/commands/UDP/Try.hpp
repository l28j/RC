#ifndef __TRY_HPP__
#define __TRY_HPP__

#include "../command.hpp"

class Try : public Command{

private:
    string PLID;
    vector<string> content;
    string numberTry;


public:
  Try(vector<string> args);
  void execute() override;
};

#endif

