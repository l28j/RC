#include "commandFactory.hpp"
Command*CommandFactory::createCommand(const std::string& protocolMessage) {
  Parser parser(protocolMessage);
  string command = parser.getCommand();
  vector<string> arguments = parser.getArgs();
  
  // catch exception throwed by the constructor, in that case the command is invalid and we return NULL 
  try {
        if (command == SNG) {
            return new Start(arguments);
        } else if (command == TRY) {
            return new Try(arguments);
        } else if (command == QUT) {
            return new Quit(arguments);
        } else if (command == DBG) {
            return new Debug(arguments);
        } else if (command == STR) {
            return new Show_Trials(arguments);
        } else if (command == SSB) {
            return new Scoreboard();
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