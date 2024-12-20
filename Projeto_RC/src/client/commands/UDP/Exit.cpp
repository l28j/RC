#include "Exit.hpp"

// Executes the exit command, handling cases where the client is not playing.
int Exit::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(EXITING).c_str()); // Notify exit if no game is active.
        return 1;
    }
    int i = Command::execute(); // Execute the base command.
    if (i != 0) {
        std::cerr << "Erro ao executar comando!" << std::endl; // print execution error.
        return i;
    }
    return 1;
}

// Sends the formatted exit command to the server.
void Exit::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

// Formats the exit command with the client ID to be sent to the server.
string Exit::formatData() {
    return string(QUT) + " " + this->client->getID() + "\n";
}

// Receives and processes the server's response for the exit command.
void Exit::receive() {
    string data = "";
    try {
        data = this->networkClient->receiveData(); // Attempt to receive server response.
    } catch (const std::runtime_error& e) { // Handle UDP time out connection.
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

    // Handle server response based on its status.
    if (status == OK) {
        // Reset client state.
        this->client->setID("");
        this->client->setGameTime("");
        this->client->setTrials("0");
        this->client->setWin(false);
        this->client->setLose(false);

        // Display game over and exit messages.
        printf("%s\n", string(GAME_OVER).c_str());
        printf("%s\n", string(EXITING).c_str());

        // Display the secret code.
        printf("Secret code: %s %s %s %s\n", arguments[1].c_str(), arguments[2].c_str(), arguments[3].c_str(), arguments[4].c_str());
    }
    else if (status == NOK) {
        printf("%s\n", string(PLAYER_NOT_PLAYING).c_str()); // Notify no active game.
    }
    else {
        throw ServerResponseError(); // Handle unexpected statuses.
    }
}
