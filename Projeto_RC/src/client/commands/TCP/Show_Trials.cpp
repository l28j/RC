#include "Show_Trials.hpp"

// Executes the Show_Trials command, verifying if the player is currently playing.
int Show_Trials::execute() {
    if (this->client->getID().empty()) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
        return 0;
    }
    return Command::execute();
}

// Sends the formatted Show_Trials command to the server.
void Show_Trials::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the data to send to the server, including the player's ID.
string Show_Trials::formatData() {
    return string(STR) + " " + this->client->getID() + "\n";
}

// Handles the server's response for the Show_Trials command.
void Show_Trials::receive() {
    string data = this->networkClient->receiveData();

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Validate the command and its response.
    if (command == ERR || command != RST ) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];   
    
    if (status == ACT || status == FIN) {
        // Handle active or finalized game response.
        string file_name = arguments[1];
        string file_size = arguments[2];
        string input = parser.getInput();
        size_t pos = input.find(file_size);
        string content_to_show = input.substr(pos + file_size.length() + 1);
        printf("%s\n", content_to_show.c_str()); // Print the game content.

        // Save the response to a file.
        Fs file = Fs(file_name);
        file.open(WRITE);
        file.write(&content_to_show);
        file.close();
        printf("File name: %s\n", file_name.c_str());
        printf("File size: %s\n", file_size.c_str());
        if (status == FIN) {
            this->client->setID("");
            this->client->setGameTime("");
            this->client->setTrials("0");
            this->client->setWin(false);
            this->client->setLose(false);
        }
    }
   
    else if (status == NOK) {
        // No games available for the player.
        printf("%s\n", string(NO_GAMES).c_str());
    }
    else {
        throw ServerResponseError();
    }
}
