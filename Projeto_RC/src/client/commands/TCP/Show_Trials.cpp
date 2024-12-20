#include "Show_Trials.hpp"

// Executes the command if the client is playing; otherwise, displays no game message.
int Show_Trials::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(NO_GAMES).c_str());
        return 0;
    }
    return Command::execute();
}

// Sends the formatted command to the server.
void Show_Trials::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the data with the client ID to be sent to the server.
string Show_Trials::formatData() {
    return string(STR) + " " + this->client->getID() + "\n";
}

// Receives and processes the response from the server.
void Show_Trials::receive() {
    string data = this->networkClient->receiveData();
    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Handle error responses or unexpected commands.
    if (command == ERR || command != RST) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];
    printf("STATUS: %s\n", status.c_str()); // Display the status.

    // Extract content sent by file and displays
    if (status == ACT || status == FIN) {
        string file_name = arguments[1];
        string file_size = arguments[2];
        string input = parser.getInput();
        size_t pos = input.find(file_size);
        string content_to_show = input.substr(pos + file_size.length() + 1);
        printf("%s\n", content_to_show.c_str()); // Display trials content.

        Fs file = Fs(file_name); // Create a file object with the given name.
        file.open(WRITE);
        file.write(&content_to_show); // Write trials content to the file.
        file.close();
    }
    // Handle no ongoing games.
    else if (status == NOK) {
        printf("%s\n", string(NO_GAMES).c_str());
    }
    // Handle unexpected statuses.
    else {
        throw ServerResponseError();
    }
}
