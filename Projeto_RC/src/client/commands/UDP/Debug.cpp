#include "Debug.hpp"

// Executes the command if the player is not currently playing; otherwise, prints error
int Debug::execute() {
    if(this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_IS_PLAYING).c_str());
        return 0;
    }
    return Command::execute();
}

// Sends the formatted command to the server.
void Debug::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the debug command with client information to be sent to the server.
string Debug::formatData() {
    return string(DBG) + " " + this->ID + " " + this->game_time + " " + this->content + "\n";
}

// Receives and processes the server's response for the debug command.
void Debug::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData(); // Try to receive data from the server.
    } catch (const std::runtime_error& e) { // Handle UDP connection timeout error.
        std::cout << "Error: " << e.what() << std::endl;
        return;
    }

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Generates error after server response
    if (command == ERR || command != RDB || arguments.size() != 1) {
        throw ServerResponseError();
    }

    string status = arguments[0];   

    // Handle the response based on its status.
    if (status == OK) {
        this->client->setID(this->ID); // Update client ID.
        this->client->setGameTime(this->game_time); // Update game time.
        printf("%s\n", string(GAME_START).c_str()); // Indicate the game has started.
    }
    else if (status == NOK) {
        printf("%s\n", string(ONGOING_GAME).c_str()); // Notify of an ongoing game.
    }
    else if (status == ERR) {
        printf("%s\n", string(INVALID_COMMAND_DEBUG).c_str()); // Notify of an invalid command.
        printf("%s\n", string(AVAILABLE_COLORS).c_str()); // Display expected command format
    }
    else {
        throw ServerResponseError(); // Throw an error for unexpected statuses.
    }
}
