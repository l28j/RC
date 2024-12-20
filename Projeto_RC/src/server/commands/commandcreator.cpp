#include "commandcreator.hpp"

/**
 * @brief Factory method to create a command object based on the protocol message.
 * Parses the incoming message, identifies the command, and creates the corresponding object.
 * @param protocolMessage The string containing the protocol message.
 * @return Command* A pointer to the created command object, or nullptr if the command is invalid.
 */
Command* CommandFactory::createCommand(const std::string& protocolMessage) {

    Parser parser(protocolMessage);
    string command = parser.getCommand();          // Get the command name
    vector<string> arguments = parser.getArgs();   // Get the command arguments
    
    // Catch exceptions thrown by the constructor for validation failures
    try {
        if (command == SNG) {
            return new Start(arguments);           // Create a Start command
        } else if (command == TRY) {
            return new Try(arguments);             // Create a Try command
        } else if (command == QUT) {
            return new Quit(arguments);            // Create a Quit command
        } else if (command == DBG) {
            return new Debug(arguments);           // Create a Debug command
        } else if (command == STR) {
            return new Show_Trials(arguments);     // Create a Show_Trials command
        } else if (command == SSB) {
            return new Scoreboard();               // Create a Scoreboard command (no arguments)
        }
    } catch (const std::exception& e) {
        // Handle validation failure by logging the error and returning nullptr
        printf("Command constructor failed because of validations: %s\n", e.what());
        return nullptr;
    }

    // Clean up the parser explicitly
    parser.~Parser();

    // Return nullptr if the command does not match any of the predefined types
    return nullptr;
}
