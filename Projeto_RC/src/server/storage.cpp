#include "storage.hpp"
#include <string>
#include <filesystem>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <dirent.h>

// Creates a new game file for a player with the provided arguments and mode.
void createGame(vector<string> arguments, string mode) {
    string dir_path = "src/server/_GAMES";
    namespace fs = std::filesystem;

    // Create the directory if it doesn't exist.
    if (!fs::exists(dir_path)) {
        fs::create_directory(dir_path);
    }

    // Build the path to the game file.
    string path = dir_path + "/" + string("GAME") + "_" + arguments[0] + ".txt";

    Fs file = Fs(path);

    // Open the file for writing.
    int error = file.open(WRITE);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    // Write game data to the file.
    string data = arguments[0] + " " + mode + " " + arguments[1] + " " + arguments[2] + " " + 
                  arguments[3] + " " + arguments[4] + " " + " \n";

    error = file.write(&data);
    if (error < 0) {
        throw runtime_error("Failed to write to file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }
}

// Ends a game for the specified player ID (PLID) and updates relevant files based on the status.
void endGame(string PLID, string status) {
    string dir_path = "src/server/_GAMES/" + PLID + "/";
    namespace fs = std::filesystem;

    // Create the directory for the player if it doesn't exist.
    if (!fs::exists(dir_path)) {
        fs::create_directory(dir_path);
        if (!fs::exists(dir_path)) {
            throw runtime_error("Failed to create directory");
        }
    }

    // Generate a new file path with timestamp and status.
    time_t full_time;
    struct tm* nowLocal;
    string time_remaining = "";

    secondsRemaining(PLID, &time_remaining);
    time(&full_time);

    nowLocal = gmtime(&full_time);
    nowLocal->tm_year += 1900;
    nowLocal->tm_mon += 1;

    std::ostringstream oss1;
    // Formats the values with zeros at the left if needed
    oss1 << dir_path
        << std::setw(4) << nowLocal->tm_year // Years
        << std::setw(2) << std::setfill('0') << nowLocal->tm_mon // Months
        << std::setw(2) << std::setfill('0') << nowLocal->tm_mday << "_" // Days
        << std::setw(2) << std::setfill('0') << nowLocal->tm_hour // Hours
        << std::setw(2) << std::setfill('0') << nowLocal->tm_min // MInutes
        << std::setw(2) << std::setfill('0') << nowLocal->tm_sec << "_" // Seconds
        << status << ".txt";
    string new_path = oss1.str(); // Sets "new_path" with the new formated string

    // Update the scoreboard if the player has won.
    if (status == "W") {
        string score_dir = "src/server/_SCORES/";
        if (!fs::exists(score_dir)) {
            fs::create_directory(score_dir);
        }

        std::ostringstream oss2;
        // Formats the values with zeros at the left if needed
        oss2 << score_dir << "_" << PLID
            << "_" << std::setw(2) << std::setfill('0') << nowLocal->tm_mday // Days
            << "_" << std::setw(2) << std::setfill('0') << nowLocal->tm_mon  // Months
            << "_" << std::setw(4) << nowLocal->tm_year                      // Years
            << "_" << std::setw(2) << std::setfill('0') << nowLocal->tm_hour // Hours
            << std::setw(2) << std::setfill('0') << nowLocal->tm_min         // Minutes
            << std::setw(2) << std::setfill('0') << nowLocal->tm_sec         // Seconds
            << ".txt";
        string score_path = oss2.str(); // Sets "score_path" with the new formated string

        Fs file = Fs(score_path);
        int error = file.open(WRITE);
        if (error < 0) {
            throw runtime_error("Failed to open file");
        }

        string trials = "";
        string score_str = "";
        string max_time = "";
        string game_time = "";
        string num_trials = "";
        string secret_code = "";
        string game_mode = "";

        getMaxTime(PLID, &max_time);
        getTrials(PLID, &trials, &num_trials);
        getSecretCode(PLID, &secret_code);
        getMode(PLID, &game_mode);
        game_time = to_string(stoi(max_time) - stoi(time_remaining));

        int score_int = score(stoi(max_time), stoi(game_time), stoi(num_trials));
        score_str = to_string(score_int);
        game_mode = (game_mode == "P") ? "PLAY" : "DEBUG";

        string data = score_str + " " + PLID + " " + secret_code + " " + num_trials + " " + game_mode + "\n";
        error = file.write(&data);
        if (error < 0) {
            throw runtime_error("Failed to write to file");
        }

        error = file.close();
        if (error < 0) {
            throw runtime_error("Failed to close file");
        }
    }

    // Update the game file with the end time and status.
    Fs file = Fs("src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt");
    int error;

    string max_time = "";
    getMaxTime(PLID, &max_time);
    int game_time = stoi(max_time) - stoi(time_remaining);
    string game_time_str = to_string(game_time);

    std::ostringstream oss3;
    // Places zeros at the left of each parameter if needed
    oss3 << std::setw(4) << (nowLocal->tm_year) // Years
        << "-" << std::setw(2) << std::setfill('0') << nowLocal->tm_mon // Months
        << "-" << std::setw(2) << std::setfill('0') << nowLocal->tm_mday // Days
        << " " << std::setw(2) << std::setfill('0') << nowLocal->tm_hour // Hours
        << ":" << std::setw(2) << std::setfill('0') << nowLocal->tm_min  // Minutes
        << ":" << std::setw(2) << std::setfill('0') << nowLocal->tm_sec  // Seconds
        << " " << game_time_str << " \n";
    std::string end_line = oss3.str(); // sets "end_line" with the new formated string

    error = file.open(WRITE);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    error = file.writeOnNewLine(&end_line);
    if (error < 0) {
        throw runtime_error("Failed to write to file");
    }

    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    file.rename(&new_path); // Rename the game file with the new path.
}


// Calculates the score based on max time, game time, and number of trials.
int score(int max_time, int game_time, int num_trials) {
    int result = 100 * (0.4 * ((600.0 - max_time) / 600.0) +
                        0.3 * ((max_time - game_time) / (float)max_time) +
                        0.2 * ((8.0 - num_trials) / 8.0));
    return result;
}

// Extracts the argument at the specified index from a space-separated string.
string getArgument(string arguments, int index) {
    vector<string> args;
    stringstream ss(arguments);
    string arg;

    // Split the arguments string into a vector of strings.
    while (getline(ss, arg, ' ')) {
        args.push_back(arg);
    }

    // Return the argument at the specified index or an empty string if index is invalid.
    if (index < 0 || index >= static_cast<int>(args.size())) {
        return "";
    }
    return args[index];
}

// Retrieves the mode (e.g., PLAY or DEBUG) from the game file.
void getMode(string PLID, string* mode) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line;

    // Read the first line from the file.
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Extract the mode argument from the first line.
    string mode_str = getArgument(first_line, 1);
    if (mode_str == "") {
        throw runtime_error("Failed to find the second argument in the first line");
    }

    *mode = mode_str;
}

// Retrieves the secret code from the game file.
void getSecretCode(string PLID, string* secret_code) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line;

    // Read the first line from the file.
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Extract the secret code argument from the first line.
    string secret_code_str = getArgument(first_line, 2);
    if (secret_code_str == "") {
        throw runtime_error("Failed to find the third argument in the first line");
    }

    *secret_code = secret_code_str;
}

// Retrieves the game time and full timestamp from the game file.
void getGameTime(string PLID, string* game_time) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line;

    // Read the first line from the file.
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Extract the game time and full timestamp arguments from the first line.
    string game_time_str = getArgument(first_line, 4);
    string full_time_str = getArgument(first_line, 5);

    if (game_time_str == "" || full_time_str == "") {
        throw runtime_error("Failed to find the fourth and fifth arguments in the first line");
    }

    *game_time = game_time_str + " " + full_time_str;
}


// Retrieves the maximum game time from the game file.
void getMaxTime(string PLID, string* max_time) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line;

    // Read the first line from the file.
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Extract the max time from the first line.
    string max_time_str = getArgument(first_line, 3);
    if (max_time_str == "") {
        throw runtime_error("Failed to find the second argument in the first line");
    }

    *max_time = max_time_str;
}

// Calculates the remaining seconds in the game.
void secondsRemaining(string PLID, string* seconds) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line;

    // Read the first line from the file.
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Extract max time and full timestamp from the first line.
    string max_time_str = getArgument(first_line, 3);
    string full_time_str = getArgument(first_line, 6);

    if (max_time_str == "" || full_time_str == "") {
        throw runtime_error("Failed to find the fourth and fifth arguments in the first line");
    }

    // Calculate remaining time.
    time_t now = time(NULL);
    int remaining = stoi(max_time_str) - (now - stoi(full_time_str));

    *seconds = to_string(remaining);
}

// Retrieves all trial details and counts the number of trials.
void getTrials(string PLID, string* trials, string* num_trials) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the file.
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string data;

    // Read the file contents.
    error = file.read(&data);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Close the file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Ignore the first line.
    size_t pos = data.find("\n");
    if (pos == string::npos) {
        throw runtime_error("Failed to find the first newline character");
    }
    data = data.substr(pos + 1);
    string temp = data;

    // Count the number of trials.
    int count = 0;
    pos = temp.find("\n");
    while (pos != string::npos) {
        count++;
        temp = temp.substr(pos + 1);
        pos = temp.find("\n");
    }

    *trials = data; // Store all trials as a single string.
    *num_trials = to_string(count); // Store the count of trials.
}

// Checks if the player can continue playing the game.
int canPlay(string PLID) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    namespace fs = std::filesystem;

    // Check if the game file exists.
    if (!fs::exists(path)) {
        return 0;
    }

    string time_remaining;
    secondsRemaining(PLID, &time_remaining);

    // Check if time remaining is greater than zero.
    if (stoi(time_remaining) <= 0) {
        return 0;
    }

    return 1;
}

// Checks if a player currently has an active game.
int playerISPlaying(string PLID) {
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    namespace fs = std::filesystem;

    // Return true if the game file exists, false otherwise.
    return fs::exists(path) ? 1 : 0;
}


// Checks if the current trial is a duplicate of previous ones.
int isDup(string PLID, vector<string> content) {
    int dup_flag = 0;
    string trials = "";
    string n_trials = "";

    // Retrieve all trials and their count.
    getTrials(PLID, &trials, &n_trials);

    // If there are no trials, return no duplicate.
    if (n_trials == "0") {
        return 0;
    }

    // Combine the content into a single string.
    string combined_content = content[0] + content[1] + content[2] + content[3];

    // Iterate over each trial.
    for (int i = 0; i < stoi(n_trials); i++) {
        string trial = "";
        size_t pos = trials.find("\n");
        if (pos == string::npos) {
            throw runtime_error("Failed to find the first newline character");
        }
        trial = trials.substr(0, pos);
        trials = trials.substr(pos + 1);

        string code = getArgument(trial, 1);

        if (combined_content == code) {
            if (i == stoi(n_trials) - 1) {
                return 2; // Exact duplicate of the most recent trial.
            } else {
                dup_flag = 1; // Duplicate exists but not the most recent.
            }
        }
    }

    return dup_flag == 1 ? 1 : 0;
}

// Verifies the validity of the trial number against the game's trial count.
int checkTrial(string PLID, string trial) {
    string trials = "";
    string num_trials = "";

    // Retrieve all trials and their count.
    getTrials(PLID, &trials, &num_trials);

    if (stoi(trial) == stoi(num_trials)) {
        return 2; // Trial matches the most recent.
    }

    if (stoi(trial) == stoi(num_trials) + 1) {
        return 1; // Trial is valid as the next expected trial.
    }

    return 0; // Invalid trial.
}

// Compares the player's trial against the secret code.
void compare_code(string secret_code, string trial, int* corrects, int* wrongs) {
    *corrects = 0;
    *wrongs = 0;

    vector<bool> matched_secret(4, false); 
    vector<bool> matched_trial(4, false); 

    // Check for correct positions.
    for (int i = 0; i < 4; i++) {
        if (secret_code[i] == trial[i]) {
            (*corrects)++;
            matched_secret[i] = true;
            matched_trial[i] = true;
        }
    }

    // Check for correct colors in wrong positions.
    for (int i = 0; i < 4; i++) {
        if (!matched_trial[i]) { 
            for (int j = 0; j < 4; j++) {
                if (!matched_secret[j] && trial[i] == secret_code[j]) { 
                    (*wrongs)++;
                    matched_secret[j] = true; 
                    break;
                }
            }
        }
    }
}

// Executes a player's trial and updates the game state accordingly.
void try_command(string PLID, vector<string> colors, string numberTry, string* status, string* data) {
    string secret_code = "";
    getSecretCode(PLID, &secret_code);

    if (secret_code == "") {
        throw runtime_error("Failed to get secret code");
    }

    string str_content = colors[0] + colors[1] + colors[2] + colors[3];

    int corrects_int = 0;
    int wrongs_int = 0;

    // Compare the trial with the secret code.
    compare_code(secret_code, str_content, &corrects_int, &wrongs_int);

    string corrects = to_string(corrects_int);
    string wrongs = to_string(wrongs_int);

    // Determine the trial outcome.
    string end_code = "";
    if (corrects_int != 4 && numberTry == "8") {
        *status = "ENT";
        end_code = "F"; // Game over, maximum attempts reached.
    } else if (corrects_int == 4) {
        *status = "OK";
        end_code = "W"; // Player wins.
    } else {
        *status = "OK"; // Trial is valid but game continues.
    }

    string time_remaining = "";
    string max_time = "";
    secondsRemaining(PLID, &time_remaining);
    getMaxTime(PLID, &max_time);

    string seconds = to_string(stoi(max_time) - stoi(time_remaining));

    // Format the trial entry.
    string trial = "T: " + str_content + " " + corrects + " " + wrongs + " " + seconds + " \n";

    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";
    Fs file = Fs(path);

    // Open the game file.
    int error = file.open(WRITE);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    // Write the trial data to the game file.
    error = file.writeOnNewLine(&trial);
    if (error < 0) {
        throw runtime_error("Failed to write to file");
    }

    // Close the game file.
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Prepare the response data.
    *data = "";
    if (*status == "OK") {
        *data = numberTry + " " + corrects + " " + wrongs;
    } else {
        for (int i = 0; i < 4; i++) {
            *data += std::string(1, secret_code[i]) + " ";
        }
    }

    // End the game if necessary.
    if (end_code != "") {
        endGame(PLID, end_code);
    }
}


int findTopScores(SCORELIST *list){
    struct dirent **file_list;  // Directory entries
    int n_entries, ifile = 0;
    char filename[300];         // Buffer for file path
    FILE *fp;

    // Scan the SCORES directory and sort entries alphabetically
    n_entries = scandir("src/server/_SCORES/", &file_list, nullptr, alphasort);
    if (n_entries <= 0) {
        return 0;  // No valid entries found
    }

    // Process each file in the SCORES directory
    while (n_entries--) {
        // Skip hidden files (names starting with '.')
        if (file_list[n_entries]->d_name[0] != '.' && ifile < 10) {
            snprintf(filename, sizeof(filename), "src/server/_SCORES/%s", file_list[n_entries]->d_name);

            // Open the file in read mode
            fp = fopen(filename, "r");
            if (fp != nullptr) {
                // Read and store data into SCORELIST
                fscanf(fp, "%d %s %s %d %s",
                       &list->score[ifile],
                       list->PLID[ifile],
                       list->colcode[ifile],
                       &list->ntries[ifile],
                          list->mode[ifile]);

                fclose(fp);  // Close the file
                ++ifile;     // Increment valid file counter
            }
        }

        free(file_list[n_entries]);  // Free memory for the current entry
    }

    free(file_list);         // Free the file list
    list->n_scores = ifile;  // Update the number of scores

    return ifile;  // Return the number of files processed
}


void sortScores(SCORELIST &list) {
    std::vector<int> indices(list.n_scores);
    
    for (int i = 0; i < list.n_scores; ++i) 
        indices[i] = i;

    // Sort indices based on score values, descendent order
    std::sort(indices.begin(), indices.end(), [&list](int a, int b){
        return list.score[a] > list.score[b];
    });

    // Temporary list to hold sorted values
    SCORELIST temp = list;

    for (int i = 0; i < list.n_scores; ++i) {
        int idx = indices[i];
        list.score[i] = temp.score[idx];
        strcpy(list.PLID[i], temp.PLID[idx]);
        strcpy(list.colcode[i], temp.colcode[idx]);
        list.ntries[i] = temp.ntries[idx];
        strcpy(list.mode[i], temp.mode[idx]);
    }
}

    