#include "commandcreator.hpp"

Command* CommandFactory::createCommand(string protocolMessage) {
  Parser parser(protocolMessage);
  string command = parser.getCommand();
  vector<string> arguments = parser.getArgs();

  // catch exception throwed by the constructor, in that case the command is invalid and we return NULL 
  try {
    if (command == SNG){
      // printf("Creating login command\n");
      return new Start(arguments);
    }
    else if (command == TRY){
      // printf("Creating logout command\n");
      return new Try(arguments);
    }
    else if (command == QUT){
      // printf("Creating unregister command\n");
      return new Quit(arguments);
    }
    else if (command == DBG){
      // printf("Creating listmyauctions command\n");
      return new Debug(arguments);
    }
    else if (command == STR){
      // printf("Creating listmybids command\n");
      return new Show_trials(arguments);
    }
    else if (command == SSB){
      // printf("Creating list command\n");
      return new Scoreboard(arguments);
    }
    else if (command == "SRC"){
      // printf("Creating show record command\n");
      return new ShowRecord(arguments);
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