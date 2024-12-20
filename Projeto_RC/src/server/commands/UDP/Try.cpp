#include "Try.hpp"

#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <random>

// Constructor: Initializes the Try object with arguments and sets initial parameters.
Try::Try(vector<string> args) {
    this->socketType = "UDP";
    this->returnCode = RTR;

    this->PLID = args[0];
    int i = 0;
    this->content.resize(4);

    // Extract color inputs from arguments.
    for (i = 0; i < 4; i++) {
        this->content[i] = args[i + 1];
    }

    this->numberTry = args[5];

    // Validate arguments.
    if (!(Verify::isUID(this->PLID) && Verify::isNumber(this->numberTry) && stoi(this->numberTry) >= 0)) {
        this->status = ERR;
    }

    for (i = 0; i < 4; i++) {
        if (!(Verify::isColor(this->content[i]))) {
            this->status = ERR;
        }
    }

    if (stoi(this->numberTry) > 8 || stoi(this->numberTry) < 0) {
        this->status = INV;
    }
}

// Executes the Try command to process a player's trial attempt.
void Try::execute() {

    // Check if arguments are valid.
    if ((this->status == ERR) || (this->status == INV)) {
        this->send(this->status); // Send error or invalid status.
        return;
    }

    // Check if the player has an active game.
    if (!playerISPlaying(this->PLID)) {
        this->status = NOK; // Set status to NOT OK if no active game is found.
        send(this->status);
        return;
    }

    // Check if the player is eligible to continue playing.
    if (!canPlay(this->PLID)) {
        this->status = ETM; // Set status to TIME IS OVER.
        string secret_code = "";
        getSecretCode(this->PLID, &secret_code);

        // Append the secret code to the status.
        for (int i = 0; i < 4; i++) {
            this->status += " " + std::string(1, secret_code[i]);
        }
        send(this->status);
        endGame(this->PLID, "T"); // End the game with reason "Time".
        return;
    }

    int dup = 0, trial = 0;

    // Check for duplicate attempts and valid trial number.
    dup = isDup(this->PLID, this->content);
    trial = checkTrial(this->PLID, this->numberTry);

    if (dup == 2 && trial == 2) {
        this->status = OK; // Set status to OK to recover from possible TIMEOUT in previous trial
        send(this->status);
        return;
    } else if (trial == 0 || (trial == 2 && dup != 2)) {
        this->status = INV; // Set status to INVALID if trial is incorrect.
        send(this->status);
        return;
    } else if (dup == 1 || dup == 2) {
        this->status = DUP; // Set status to DUPLICATE for repeated attempts.
        send(this->status);
        return;
    }

    string status = "";
    string data = "";

    // trial is valid, so it gets "data" (string) ready to send
    try_command(this->PLID, this->content, this->numberTry, &status, &data);

    this->status = status;
    this->send(this->status + " " + data); // Send the status and trial result data.
}
