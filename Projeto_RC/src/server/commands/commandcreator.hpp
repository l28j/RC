#ifndef COMMAND_CREATOR_HPP
#define COMMAND_CREATOR_HPP

#include "../constants.hpp"
#include "command.hpp"
#include "../../common/common.hpp"

//include udp commands
#include "UDP/Start.hpp"
#include "UDP/Quit.hpp"
#include "UDP/Try.hpp"
#include "UDP/Debug.hpp"

//include tcp commands
#include "TCP/scoreboard.hpp"
#include "TCP/show_trials.hpp"



#include <string>
#include <vector>

class CommandFactory {
public:
  static Command *createCommand(string protocolMessage);
};

#endif