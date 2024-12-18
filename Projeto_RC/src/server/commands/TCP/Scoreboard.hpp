#ifndef __SCOREBOARD_HPP__ 
#define __SCOREBOARD_HPP__

#include "../command.hpp"
#include "../../storage.hpp"

class Scoreboard : public Command{
public:
    Scoreboard();
    void execute() override;
};

#endif
