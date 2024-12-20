#include "Try.hpp"

// Executes the try command if the player is currently playing; otherwise, prints error.
int Try::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
        return 0;
    }
    return Command::execute();
}

// Sends the formatted try command to the server.
void Try::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the try command with the current game state to be sent to the server.
string Try::formatData() {
    if (!this->client->isWin()) {
        this->client->setTrials(to_string(stoi(this->client->getTrials()) + 1)); // Increment trial count.
    }
    return string(TRY_) + " " + this->client->getID() + " " + this->content[0] + " " + this->content[1] + " " + this->content[2] + " " + this->content[3] + " " + this->client->getTrials() + "\n";
}

// Receives and processes the server's response for the try command.
void Try::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData(); // Attempt to receive the server response.
    } catch (const std::runtime_error& e) { // Handle reception errors.
        std::cout << "Error: " << e.what() << std::endl;
        this->client->setTrials(to_string(stoi(this->client->getTrials()) - 1)); // Decrement trial count on error as timeout occured.
        return;
    }

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Validate the command and arguments received.
    if (command == ERR || command != RTR || (arguments.size() != 1 && arguments.size() != 4 && arguments.size() != 5)) {
        throw ServerResponseError();
    }

    string status = arguments[0];

    // Handle server response based on the status.
    if (status == OK) {
        if (arguments.size() != 4) {
            throw ServerResponseError();
        } else if (arguments[2] == "4") {
            printf("%s\n", string(WIN).c_str()); // Player wins the game.
            this->client->setWin(true);
        } else {
            printf("Try nº: %s\n", arguments[1].c_str());
            printf("Right: %s\n", arguments[2].c_str());
            printf("Wrong: %s\n", arguments[3].c_str());
        }
    } else if (status == DUP) {
        printf("%s\n", string(DUPLICATE).c_str()); // Notify duplicate trial.
        this->client->setTrials(to_string(stoi(this->client->getTrials()) - 1));
    } else if (status == INV) {
        printf("%s\n", string(INVALID).c_str()); // Notify invalid trial.
    } else if (status == ENT) {
        if (arguments.size() != 5) {
            throw ServerResponseError();
        } else {
            printf("%s\n", string(GAME_OVER).c_str()); // Notify game over.
            printf("Secret code: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
            this->client->setLose(true);
        }
    } else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str()); // Notify no active game.
    } else if (status == ETM) {
        printf("%s\n", string(TIME_IS_OVER).c_str()); // Notify time is over.
        printf("Secret: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
        this->client->setLose(true);
    } else if (status == ERR) {
        printf("%s\n", string(INVALID_COMMAND_TRY).c_str()); // Notify invalid command.
        printf("%s\n", string(AVAILABLE_COLORS).c_str()); // Display available options.
    } else {
        throw ServerResponseError(); // Handle unexpected responses.
    }
}
