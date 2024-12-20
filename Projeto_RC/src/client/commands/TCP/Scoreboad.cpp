
#include "Scoreboard.hpp"


int Scoreboard::execute() {
    return Command::execute();
}

// Sends the formatted command to the server via the network client.
void Scoreboard::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the command to be sent to server.
string Scoreboard::formatData() {
    return string(SSB) + "\n";
}

// Receives a response from the server with Scoreboard content.
void Scoreboard::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Handle error responses or unexpected commands.
    if (command == ERR || command != RSS) {
        throw ServerResponseError();
    }

    else if ( command == RSS && arguments[0] == OK) {
        string input = parser.getInput();
        string content_to_show;
        string file_name = arguments[1]; // Extract the file name argument.
        string file_size = arguments[2]; // Extract the file size argument.

        // Find the content starting after the file size.
        size_t pos = input.find(file_size);
        content_to_show = input.substr(pos + file_size.length() + 1);
        printf("%s\n", content_to_show.c_str()); //Print Scoreboard to terminal

        Fs file = Fs(file_name); // Create a file object with the given name.
        file.open(WRITE);
        file.write(&content_to_show); // Write the Scoreboard to the file.
        file.close();
    }
    else if (command == RSS && arguments[0] == EMPTY) {
        printf("%s\n", string(EMPTY_SCOREBOARD).c_str());
    }
    else {
        throw ServerResponseError();
    }
}
        

        
        

            

        



