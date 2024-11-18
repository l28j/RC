#ifndef __SHOWASSET_HPP__
#define __SHOWASSET_HPP__

#include "../command.hpp"

class ShowAsset : public Command
{
private:
  string aid;

public:
  ShowAsset(vector<string> args);
  void execute() override;
};

#endif
