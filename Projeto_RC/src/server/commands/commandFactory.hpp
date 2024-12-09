#ifndef __COMMAND_FACTORY_HPP__
#define __COMMAND_FACTORY_HPP__

#include "../constants.hpp"
#include "command.hpp"
#include "../../common/common.hpp"

//include udp commands
#include "UDP/login.hpp"
#include "UDP/logout.hpp"
#include "UDP/unregister.hpp"
#include "UDP/myauctions.hpp"
#include "UDP/mybids.hpp"
#include "UDP/list.hpp"
#include "UDP/showrecord.hpp"

//include tcp commands
#include "TCP/open.hpp"
#include "TCP/close.hpp"
#include "TCP/showasset.hpp"
#include "TCP/bid.hpp"


#include <string>
#include <vector>

class CommandFactory {
public:
  static Command *createCommand(string protocolMessage);
};

#endif