#include "Start.hpp"

// Executes the start command if the client is not already playing.
int Start::execute() {
    if (this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_IS_PLAYING).c_str()); // Notify that the player is already playing.
        return 0;
    }
    return Command::execute();
}

// Sends the formatted start command to the server.
void Start::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the start command with client details to be sent to the server.
string Start::formatData() {
    return string(SNG) + " " + this->ID + " " + this->game_time + "\n";
}

// Receives and processes the server's response for the start command.
void Start::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData(); // Attempt to receive the server response.
    } catch (const std::runtime_error& e) { // Handle any errors during data reception.
        std::cout << "Error: " << e.what() << std::endl;
        return;
    }

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Validate the command and arguments received.
    if (command == ERR || command != RSG || arguments.size() != 1) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];

    // Handle the server response based on the status.
    if (status == OK) {
        this->client->setID(this->ID); // Update the client ID.
        this->client->setGameTime(this->game_time); // Set the game time.
        printf("%s\n", string(GAME_START).c_str()); // Notify that the game has started.
    }
    else if (status == NOK) {
        printf("%s\n", string(ONGOING_GAME).c_str()); // Notify of an ongoing game.
    }
    else {
        throw ServerResponseError(); // Handle unexpected responses.
    }
}
