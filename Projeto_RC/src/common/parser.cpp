#include "common.hpp"

#include <sstream>

using namespace std;

/**
 * Class used to parse strings using spaces as delimiters
 * - command is the first word of the string
 * - args is a vector of all words except the first
 */
Parser::Parser(string input) {
    this->input = input;

    stringstream ss(input);

    vector<string> tokens;

    string s;

    int i = 0;

    while(getline(ss, s, ' ')) {
        if(i == 0) {
            this->command = s;
        } else {
            this->args.push_back(s);
        }

        i++;
    }

}

// returns first word of input
string Parser::getCommand() {
    return this->command;
}

// returns all words of input except the first in a vector
vector<string> Parser::getArgs() {
    return this->args;
}

string Parser::getInput() {
    return this->input;
}
