#include "Show_Trials.hpp"

// Constructor: Initializes the Show_Trials object with arguments and sets initial parameters.
Show_Trials::Show_Trials(vector<string> args) {
    this->socketType = "TCP";
    this->returnCode = RST;

    this->PLID = args[0]; // Set player ID.

    // Verify if the player ID is valid.
    if (!Verify::isUID(this->PLID)) {
        this->status = ERR;
    }
}

// Executes the Show_Trials command to retrieve and send trial details.
void Show_Trials::execute() {

    // Verify if the arguments are valid.
    if (this->status == ERR) {
        this->send(this->status); // Send error status if arguments are invalid.
        return;
    }

    // Verify if the player is currently playing.
    if (!playerISPlaying(this->PLID)) {
        this->status = FIN; // Set status to FINISHED if no active game is found.
        this->send(this->status);
        return;
    }

    string file_name = "STATE_" + this->PLID + ".txt"; // Generate file name for player state.
    string data = " ";

    //header of the content
    data += "\t" + string("Active game found for player") + " " + this->PLID + "\n";
    data += "Game initiated:" + string(" ");

    // File path for the player's game data.
    string path = "src/server/_GAMES/" + string("GAME") + "_" + this->PLID + ".txt";

    Fs file = Fs(path);

    // Attempt to open the game file.
    int error = file.open(READ);
    if (error < 0) {
        this->status = NOK; // Set status to NOT OK if file open fails.
        this->send(this->status);
        throw runtime_error("Failed to open file");
    }

    string max_time = "";
    string game_time = "";

    // Get the maximum and current game time.
    try {
        getMaxTime(this->PLID, &max_time);
        getGameTime(this->PLID, &game_time);
    } catch (const runtime_error& e) {
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get game time or max time");
    }
    
    //Continuation of the header of the content
    data += game_time + " " + "with" + " " + max_time + " " + "seconds to be completed\n";
    data += "\n";

    string num_trials = "";
    string trials = "";

    // Get the number of trials and their details.
    try {
        getTrials(this->PLID, &trials, &num_trials);
    } catch (const runtime_error& e) {
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get trials");
    }
    //Continuation of the header of the content
    data += "\t" + string("--- ") + "Transactions found: " + num_trials + " ---\n";
    data += "\n";
    data += trials;

    string time_remaining = "";

    // Get the remaining time for the game.
    try {
        secondsRemaining(this->PLID, &time_remaining);
    } catch (const runtime_error& e) {
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get time remaining");
    }

    data += "\n";
    data += " -- " + time_remaining + " " + "seconds remaining to be completed --\n";

    string file_size = to_string(data.length()); // Calculate the data size.

    this->status = ACT; // Set status
    this->send(this->status + " " + file_name + " " + file_size + " " + data); // Send the response.
}
