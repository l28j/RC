#include "commandFactory.hpp"

Command* CommandFactory::createCommand(string protocolMessage) {
  Parser parser(protocolMessage);
  string command = parser.getCommand();
  vector<string> arguments = parser.getArgs();

  // catch exception throwed by the constructor, in that case the command is invalid and we return NULL 
  try {
    if (command == "LIN"){
      // printf("Creating login command\n");
      return new Login(arguments);
    }
    else if (command == "LOU"){
      // printf("Creating logout command\n");
      return new Logout(arguments);
    }
    else if (command == "UNR"){
      // printf("Creating unregister command\n");
      return new Unregister(arguments);
    }
    else if (command == "LMA"){
      // printf("Creating listmyauctions command\n");
      return new MyAuctions(arguments);
    }
    else if (command == "LMB"){
      // printf("Creating listmybids command\n");
      return new MyBids(arguments);
    }
    else if (command == "LST"){
      // printf("Creating list command\n");
      return new List(arguments);
    }
    else if (command == "SRC"){
      // printf("Creating show record command\n");
      return new ShowRecord(arguments);
    }
    else if (command == "OPA"){
      // printf("Creating open auction command\n");
      return new Open(arguments);
    }
    else if (command == "CLS"){
      // printf("Creating close auction command\n");
      return new Close(arguments);
    }
    else if (command == "SAS"){
      // printf("Creating show asset command\n");
      return new ShowAsset(arguments);
    }
    else if (command == "BID"){
      // printf("Creating bid command\n");
      return new Bid(arguments);
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