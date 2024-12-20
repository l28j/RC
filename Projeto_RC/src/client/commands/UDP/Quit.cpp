#include "Quit.hpp"

// Executes the quit command if the client is playing; otherwise, prints error.
int Quit::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str());
        return 0;
    }    
    return Command::execute();
}

// Sends the formatted quit command to the server.
void Quit::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the quit command with the client ID to be sent to the server.
string Quit::formatData() {
    return string(QUT) + " " + this->client->getID() + "\n";
}

// Receives and processes the server's response for the quit command.
void Quit::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData(); // Attempt to receive server response.
    } catch (const std::runtime_error& e) { // Handle errors during data reception.
        std::cout << "Error: " << e.what() << std::endl;
        return;
    }

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    // Generates error after server response
    if (command == ERR || command != RQT || (arguments.size() != 1 && arguments.size() != 5)) {
        throw ServerResponseError();
    }
    
    string status = arguments[0];

    // Handle server response based on status.
    if (status == OK) {
        // Reset client game state.
        this->client->setGameTime("");
        this->client->setTrials("0");
        this->client->setWin(false);
        this->client->setLose(false);

        // Display game over message and secret code.
        printf("%s\n", string(GAME_OVER).c_str());
        printf("Secret code: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
    }
    else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str()); // Notify no active game.
    }
    else {
        throw ServerResponseError(); // Handle unexpected responses.
    }
}
