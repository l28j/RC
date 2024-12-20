#include "Scoreboard.hpp"

// Constructor: Initializes the Scoreboard object with default socket type and return code.
Scoreboard::Scoreboard() {
    this->socketType = "TCP";
    this->returnCode = RSS;
}

// Executes the scoreboard command by retrieving and sending the top scores.
void Scoreboard::execute() {
    string file_name = "SCOREBOARD_" + string(".txt"); // Define the scoreboard file name.
    string data = " ";

    // Add the header to the scoreboard data.
    data += "\t" + string("--- Current Scoreboard (TOP10) ---") + "\n";

    SCORELIST list; // List to store scores.
    int result = findTopScores(&list); // Retrieve the top scores.

    sortScores(list); // Sort the scores.

    // If no scores are available, set status to EMPTY.
    if (result <= 0) {
        data += "No scores available.\n";
        this->status = EMPTY;
    } else {
        this->status = OK;

        // Append scores to the data string.
        for (int i = 0; i < result; i++) {
            data += (i < 9 ? "0" : "") + std::to_string(i + 1) + "   " + // Rank.
                    (list.score[i] < 100 ? (list.score[i] < 10 ? "00" : "0") : "") +
                    std::to_string(list.score[i]) + "   " + // Score.
                    std::string(list.PLID[i]) + "   " +    // Player ID.
                    std::string(list.colcode[i]) + "   " + // Color code.
                    std::to_string(list.ntries[i]) + "   " + // Number of tries.
                    std::string(list.mode[i]) + "\n";      // Mode.
        }
    }

    string size = to_string(data.length()); // Calculate the size of the data.

    // Send the status, file name, size, and data.
    this->send(this->status + " " + file_name + " " + size + " " + data);
}
