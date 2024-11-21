#ifndef COMMON_PARSER_H
#define COMMON_PARSER_H

#include <string>
#include <vector>

using namespace std;

class Parser {
    public:
        Parser(string input);
        string getCommand();
        vector<string> getArgs();
        string getInput();

    private:
        string input;
        string command;
        vector<string> args;
};

#endif