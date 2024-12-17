
#include "Scoreboard.hpp"


int Scoreboard::execute() {
    return Command::execute();
}

void Scoreboard::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Scoreboard::formatData() {
    return string(SSB) + "\n";
}

void Scoreboard::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RSS) {
        throw ServerResponseError();
    }

    else if ( command == RSS && arguments[0] == OK) {
        string input = parser.getInput();
        string content_to_show;
        string file_name = arguments[1];
        string file_size = arguments[2];

        size_t pos = input.find(file_size);
        content_to_show = input.substr(pos + file_size.length() + 1);
        printf("%s\n", content_to_show.c_str());

        Fs file = Fs(file_name);
        file.open(WRITE);
        file.write(&content_to_show);
        file.close();
    }
    else if (command == RSS && arguments[0] == EMPTY) {
        printf("%s\n", string(EMPTY_SCOREBOARD).c_str());
    }
    else {
        throw ServerResponseError();
    }
}
        

        
        

            

        



