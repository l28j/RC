#include "commandFactory.hpp"

Command* CommandFactory::createCommand(string protocolMessage) {
  Parser parser(protocolMessage);
  string command = parser.getCommand();
  vector<string> arguments = parser.getArgs();
  
  // catch exception throwed by the constructor, in that case the command is invalid and we return NULL 
  try {
    if (command == SNG){
      return new Start(arguments);
    }
    else if (command == TRY){
      return new Try(arguments);
    }
    else if (command == QUT){
      return new Quit(arguments);
    }
    else if (command == DBG){
      return new Debug(arguments);
    }
    else if (command == STR){
      return new Show_Trials(arguments);
    }
    else if (command == SSB){
      return new Start(arguments);
    }
  } catch(const std::exception& e ) {
    printf("Command constructor failed because of validations\n");
    return nullptr;
  }

  //clean parser
  parser.~Parser();

  //command doesnt exist return NULL
  return nullptr;
}