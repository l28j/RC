#include "commandParser.hpp"

/*
Parses the input string and returns a Command object
If no command is found or format is wrong returns nullptr
*/
Command* CommandParser::parseCommand(const string &input) {
    Parser parser(input);

    string command = parser.getCommand();

    vector<string> arguments = parser.getArgs();

    return CommandFactory::createCommand(command, arguments);
} 