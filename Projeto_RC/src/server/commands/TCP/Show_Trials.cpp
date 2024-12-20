#include "Show_Trials.hpp"

// Constructor for Show_Trials. Sets socket type, return code, and validates the PLID.
Show_Trials::Show_Trials(vector<string> args){
    this->socketType = "TCP";
    this->returnCode = RST;

    this->PLID = args[0];

    if (!Verify::isUID(this->PLID)){
        this->status = ERR;
    }
}

// Retrieves information about the last finalized game for a player.
string last_trial(string fname){
    string trials = "";
    int num_trials = 0;

    // Get game details and open the file.
    num_trials = getGame(fname, &trials);
    Fs file = Fs(fname);
    int error = file.open(READ);
    if (error < 0){
        return "";
    }

    // Retrieve and process the first line of the file.
    string line = "";
    error = file.getFirstLine(&line);
    if (error < 0){
        return "";
    }
    string PLID = getArgument(line, 0);
    string mode = getArgument(line, 1);
    string code = getArgument(line, 2);
    string max_time = getArgument(line, 3);
    string date = getArgument(line, 4);
    string full_time = getArgument(line, 5);

    // Retrieve and process the last line of the file.
    line = "";
    error = file.getLastLine(&line);
    if (error < 0){
        return "";
    }
    string end_date = getArgument(line, 0);
    string end_time = getArgument(line, 1);
    string duration = getArgument(line, 2);

    // Determine game mode and termination reason.
    mode == "P" ? mode = "PLAY" : mode = "DEBUG";
    string termination = " ";
    size_t pos = fname.find_last_of("_");
    termination = fname.substr(pos + 1, 1);
    if (termination == "T") termination = "Timeout";
    else if (termination == "W") termination = "Win";
    else if (termination == "F") termination = "Fail";
    else termination = "Quit";

    // Format the output data.
    string data = "";
    data += "Last finalized game for player " + PLID + "\n";
    data += "Game initiated: " + date + " " + full_time + " with " + max_time + " seconds to be completed\n";
    data += "Mode: " + mode + " " + "Secret code: " + code + "\n\n";
    if (num_trials == 0){
        data += "\t " + string("Game started - no transactions found") + "\n";
        data += "\t Termination: " + termination + " at " + end_date + " " + end_time + ", " + duration + " s\n";
    } else {
        data += "\t Game started - Transactions found: " + to_string(num_trials) + "\n";
        data += trials + "\n";
        data += "\t Termination: " + termination + " at " + end_date + " " + end_time + ", " + duration + " s\n";
    }
    return data;
}

// Executes the Show_Trials command and handles active and finalized game data.
void Show_Trials::execute(){

    // Validate arguments before proceeding.
    if (this->status == ERR){
        this->send(this->status); // Send error response if arguments are invalid.
        return;
    }

    // Handle inactive games by ending them if they have timed out.
    if (!canPlay(this->PLID) && playerISPlaying(this->PLID)){
        try {
            endGame(this->PLID, "T"); 
        } catch (const runtime_error& e){
            this->status = NOK; 
            this->send(this->status);
            throw runtime_error("Failed to end game"); 
        }
    }

    // Handle finalized games where no active game is found.
    if (!playerISPlaying(this->PLID)){
        this->status = FIN; // Set status to finalized.
        string fname = "";
        try {
            if (FindLastGame(this->PLID, &fname)){ // Attempt to find the last game data.
                string data = last_trial(fname); // Retrieve details of the last game.
                if (data == ""){
                    this->status = NOK; // Mark as not okay if no data is found.
                    this->send(this->status);
                    return;
                }
                string file_name = "STATE_" + this->PLID + ".txt"; // Name the file to save the game state.
                string file_size = to_string(data.length()); // Calculate the size of the data.
                this->status = ACT; // Set status to active for the finalized game.
                this->send(this->status + " " + file_name + " " + file_size + " " + data);
                return;
            }
        } catch (const runtime_error& e){
            this->status = NOK; // Mark as not okay if an error occurs during retrieval.
            this->send(this->status);
            throw runtime_error("Failed to find last game");
        }
        return;
    }

    
    string file_name = "STATE_" + this->PLID + ".txt";
    string data = " ";

    // Content Header
    data += "\t Active game found for player " + this->PLID + "\n";
    data += "Game initiated: ";

    // Path to the game file for the player.
    string path = "src/server/GAMES/" + string("GAME") + "_" + this->PLID + ".txt";
    Fs file = Fs(path);

    // Open the game file to retrieve details.
    int error = file.open(READ);
    if (error < 0){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to open file"); // Propagate the error if file opening fails.
    }

    string max_time = ""; // Maximum time allowed for the game.
    string game_time = ""; // Start time of the game.

    try {
        getMaxTime(this->PLID, &max_time); // Fetch the maximum time from the file.
        getGameTime(this->PLID, &game_time); // Fetch the game start time from the file.
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get game time or max time");
    }

    // Append game time details to the data.
    data += game_time + " with " + max_time + " seconds to be completed\n\n";

    string num_trials = ""; // Number of trials attempted.
    string trials = ""; // Details of the trials.

    try {
        getTrials(this->PLID, &trials, &num_trials); // Fetch trials data.
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get trials");
    }

    // Content Header
    data += "\t --- Transactions found: " + num_trials + " ---\n\n";
    data += trials;

    string time_remaining = ""; // Time remaining for the game.

    try {
        secondsRemaining(this->PLID, &time_remaining); // Calculate the remaining time.
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get time remaining");
    }

    // Append remaining time to the data.
    data += "\n -- " + time_remaining + " seconds remaining to be completed --\n";
    
    string file_size = to_string(data.length()); // Calculate data size.

    // Set status to active and send the response.
    this->status = ACT;
    this->send(this->status + " " + file_name + " " + file_size + " " + data);
}
