#ifndef __COMMAND_FACTORY_HPP__
#define __COMMAND_FACTORY_HPP__

#include "../constants.hpp"
#include "command.hpp"
#include "../../common/common.hpp"

//include udp commands
#include "UDP/Start.hpp"
#include "UDP/Quit.hpp"
#include "UDP/Debug.hpp"
#include "UDP/Try.hpp"  
#include "TCP/Show_Trials.hpp"
#include "TCP/Scoreboard.hpp"



//include tcp commands



#include <string>
#include <vector>

class CommandFactory {
public:

    static Command *createCommand(const std::string& protocolMessage);

};

#endif