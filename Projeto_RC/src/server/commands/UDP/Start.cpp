#include "Start.hpp"

#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdio>
#include <random>

// Constructor: Initializes the Start object with arguments and sets initial parameters.
Start::Start(vector<string> args) {
    this->socketType = "UDP";
    this->returnCode = RSG;

    this->PLID = args[0];
    this->timeStr = args[1];

    // Validate the player ID and game time.
    if (!Verify::isUID(this->PLID) || !Verify::isNumber(this->timeStr) || 
        stoi(this->timeStr) < 0 || stoi(this->timeStr) > MAX_TIME) {
        this->status = ERR; // Set status to ERROR if validation fails.
    }
}

// Executes the Start command to initialize a new game session.
void Start::execute() {

    // Check if arguments are valid.
    if (this->status == ERR) {
        this->send(this->status); // Send error status if arguments are invalid.
        return;
    }

    // Check if the player is already in a game.
    if (playerISPlaying(this->PLID)) {
        if (!canPlay(this->PLID)) { 
            endGame(this->PLID, "T"); 
        }
        this->status = NOK; // Set status to NOT OK if the player is already playing.
        this->send(this->status);
        return;
    }

    string code = "";
    vector<string> colors = { RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE };

    // Select 4 random colors for the secret code.
    random_device rd;
    default_random_engine rng(rd());
    shuffle(colors.begin(), colors.end(), rng);

    for (int i = 0; i < 4; i++) {
        code += colors[i];
    }

    string max_time = this->timeStr;

    time_t full_time;
    string full_time_str = "";

    struct tm* nowLocal;
    string time_str = "";

    // Get the current time and format it.
    time(&full_time);
    full_time_str = to_string(full_time);
    nowLocal = gmtime(&full_time);
    std::ostringstream oss;
    oss << (nowLocal->tm_year + 1900) << "-"
    << std::setw(2) << std::setfill('0') << (nowLocal->tm_mon + 1) << "-"
    << std::setw(2) << std::setfill('0') << nowLocal->tm_mday << " "
    << std::setw(2) << std::setfill('0') << nowLocal->tm_hour << ":"
    << std::setw(2) << std::setfill('0') << nowLocal->tm_min << ":"
    << std::setw(2) << std::setfill('0') << nowLocal->tm_sec;

    time_str = oss.str(); // Sets time_str with the formated string

    // Prepare arguments for creating the game session.
    vector<string> arguments = { this->PLID, code, max_time, time_str, full_time_str };

    // Attempt to create the game session.
    try {
        createGame(arguments, "P");
    } catch (const runtime_error& e) {
        this->returnCode = "ERR";
        this->send(this->status); // Send error status if game creation fails.
        return;
    }

    this->status = OK; // Set status to OK if the game is created successfully.
    this->send(this->status);
}
