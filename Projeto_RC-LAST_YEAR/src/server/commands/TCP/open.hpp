#ifndef __OPEN_HPP__
#define __OPEN_HPP__

#include "../command.hpp"

class Open : public Command
{
private:
  string uid;
  string password;
  string name;
  string startValue;
  string timeActive;
  string fName;
  string fSize;
  string fData;


public:
  Open(vector<string> args);
  void execute() override;
};

#endif
