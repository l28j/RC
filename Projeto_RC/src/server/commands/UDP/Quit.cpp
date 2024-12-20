#include "Quit.hpp"

// Constructor: Initializes the Quit object with arguments and sets initial parameters.
Quit::Quit(vector<string> args) {
    this->socketType = "UDP";
    this->returnCode = RQT;

    this->PLID = args[0]; // Set player ID.

    // Validate the player ID.
    if (!Verify::isUID(this->PLID)) {
        printf("Invalid PLID\n");
        this->status = ERR; // Set status to ERROR if the ID is invalid.
    }
}

// Executes the Quit command to handle game termination for the player.
void Quit::execute() {
    // Check if arguments are valid.
    if (this->status == ERR) {
        this->send(this->status); // Send error status if arguments are invalid.
        return;
    }

    // Check if the player is currently in a game.
    if (!playerISPlaying(this->PLID)) {
        this->status = NOK; // Set status to NOT OK if no active game is found.
        this->send(this->status);
        return;
    }

    string secret_code = "";
    getSecretCode(this->PLID, &secret_code); // Retrieve the secret code for the player.

    // Creates a string that contains the secret code
    string secret_code_parts;
    for (int i = 0; i < 4; i++) {
        secret_code_parts += secret_code[i];
        if (i != 3) {
            secret_code_parts += " ";
        }
    }

    endGame(this->PLID, "Q"); // End the game for the player with reason "Quit".
    this->status = OK; // Set status to OK if the game ends successfully.
    this->send(status + " " + secret_code_parts); // Send the response with the secret code.
}
