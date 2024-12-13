#ifndef __QUIT_HPP__
#define __QUIT_HPP__

#include "../command.hpp"

class Quit : public Command{

private:
  string PLID ;

public:
  Quit(vector<string> args);
  void execute() override;
};

#endif