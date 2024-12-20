#ifndef __COMMAND_FACTORY_HPP__
#define __COMMAND_FACTORY_HPP__

#include "../constants.hpp"
#include "command.hpp"
#include "../../common/common.hpp"

// Include headers for UDP commands
#include "UDP/Start.hpp"
#include "UDP/Quit.hpp"
#include "UDP/Debug.hpp"
#include "UDP/Try.hpp"

// Include headers for TCP commands
#include "TCP/Show_Trials.hpp"
#include "TCP/Scoreboard.hpp"

#include <vector>
#include <string>

/**
 * @brief A factory class for creating Command objects based on protocol messages.
 * This class determines the type of command from the given message and returns an appropriate Command instance.
 */
class CommandFactory {
public:
    /**
     * @brief Factory method to create a Command object.
     * Parses the provided protocol message, identifies the command type, and constructs the corresponding Command object.
     * @param protocolMessage A string containing the protocol message.
     * @return Command* Pointer to the created Command object, or nullptr if the command is invalid.
     */
    static Command *createCommand(const std::string& protocolMessage);
};

#endif
