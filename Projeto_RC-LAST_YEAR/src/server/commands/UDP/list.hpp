#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "../command.hpp"

class List : public Command{

public:
  List(vector<string> args);
  void execute() override;
};

#endif
