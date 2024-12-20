#include "common.hpp"
#include <sstream>

using namespace std;

/**
 * @brief Class used to parse strings using spaces as delimiters.
 * - The command is the first word of the string.
 * - The args vector contains all words except the first.
 */
Parser::Parser(string input) {
    this->input = input; // Store the full input string.

    stringstream ss(input); // Create a stringstream to split the input.
    string s;

    int i = 0;

    // Split the input into tokens based on spaces.
    while (getline(ss, s, ' ')) {
        if (i == 0) {
            this->command = s; // The first word is the command.
        } else {
            this->args.push_back(s); // Subsequent words are arguments.
        }
        i++;
    }
}

// Returns the first word of the input (the command).
string Parser::getCommand() {
    return this->command;
}

// Returns all words of the input except the first as a vector (arguments).
vector<string> Parser::getArgs() {
    return this->args;
}

// Returns the full original input string.
string Parser::getInput() {
    return this->input;
}
