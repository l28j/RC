#include "commandFactory.hpp"

std::unique_ptr<Command> CommandFactory::createCommand(const std::string& protocolMessage) {
  Parser parser(protocolMessage);
  string command = parser.getCommand();
  vector<string> arguments = parser.getArgs();
  
  // catch exception throwed by the constructor, in that case the command is invalid and we return NULL 
  try {
        if (command == SNG) {
            return std::make_unique<Start>(arguments);
        } else if (command == TRY) {
            return std::make_unique<Try>(arguments);
        } else if (command == QUT) {
            return std::make_unique<Quit>(arguments);
        } else if (command == DBG) {
            return std::make_unique<Debug>(arguments);
        } else if (command == STR) {
            return std::make_unique<Show_Trials>(arguments);
        } else if (command == SSB) {
            return std::make_unique<Scoreboard>();
        }
    } catch (const std::exception& e) {
        printf("Command constructor failed because of validations: %s\n", e.what());
        return nullptr;
    }

  //clean parser
  parser.~Parser();

  //command doesnt exist return NULL
  return nullptr;
}