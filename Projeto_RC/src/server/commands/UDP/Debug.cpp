#include "Debug.hpp"

// Constructor: Initializes the Debug object with arguments and sets initial parameters.
Debug::Debug(vector<string> args) {
    printf("Debug command\n");
    this->socketType = "UDP";
    this->returnCode = RDB;

    this->PLID = args[0];
    this->timeStr = args[1];
    this->code = "";
    
    // Concatenate the code parts into a single string.
    for (std::size_t i = 2; i < args.size(); i++) {
        this->code += args[i];
    }

    // Validate the provided arguments.
    if (!Verify::isUID(this->PLID) || !Verify::isNumber(this->timeStr) || 
        stoi(this->timeStr) < 0 || stoi(this->timeStr) > MAX_TIME) {
        this->status = ERR;
    }
    
    for (int i = 0; i < 4; i++) {
        if (!Verify::isColor(this->code.substr(i, 1))) {
            this->status = ERR;
        }
    }
}

// Executes the Debug command to set up a debug game session.
void Debug::execute() {
    // Check if arguments are valid.
    if (this->status == ERR) {
        this->send(this->status); // Send error status if arguments are invalid.
        return;
    }

    // Verify if the player is already playing.
    if (playerISPlaying(this->PLID)) {
        this->status = NOK; // Set status to NOT OK if the player is already in a game.
        this->send(this->status);
        return;
    }

    string max_time = this->timeStr; // Set the max game time.
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

    time_str = oss.str(); // Set time_str with the formated string
    
    // Prepare arguments for creating a game session.
    vector<string> arguments = { this->PLID, code, max_time, time_str, full_time_str };

    // Attempt to create the game session.
    try {
        createGame(arguments, "D");
    } catch (const runtime_error& e) {
        this->status = ERR;
        this->send(this->status); // Send error status if game creation fails.
        return;
    }

    this->status = OK; // Set status to OK if the game was created successfully.
    this->send(this->status);
}
