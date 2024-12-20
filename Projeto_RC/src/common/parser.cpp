#include "common.hpp"
#include <sstream>

using namespace std;

/**
 * @brief Class used to parse strings using spaces as delimiters.
 * - The command is the first word of the string.
 * - The args vector contains all words except the first.
 */
Parser::Parser(string input) {
    this->input = input; // Armazena a string completa de entrada.

    // Remover múltiplos espaços e tabulações consecutivos.
    stringstream cleanedInput;
    bool inWhitespace = false;
    for (char c : input) {
        if (isspace(c)) { // Verifica qualquer espaço em branco (inclui espaços, tabulações, etc.)
            if (!inWhitespace) { // Apenas insere um único espaço se não estivermos em uma sequência de espaços.
                cleanedInput << ' ';
                inWhitespace = true;
            }
        } else {
            cleanedInput << c;
            inWhitespace = false;
        }
    }

    // Processar a string limpa.
    stringstream ss(cleanedInput.str()); // Usar a string sem espaços ou tabulações consecutivos.
    string s;

    int i = 0;

    // Dividir a entrada em tokens com base em espaços.
    while (getline(ss, s, ' ')) {
        if (!s.empty()) { // Ignorar tokens vazios.
            if (i == 0) {
                this->command = s; // A primeira palavra é o comando.
            } else {
                this->args.push_back(s); // Palavras subsequentes são argumentos.
            }
            i++;
        }
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
