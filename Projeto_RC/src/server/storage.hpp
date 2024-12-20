#ifndef _STORAGE_HPP_
#define _STORAGE_HPP_

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>
#include "../common/common.hpp" 
#include "constants.hpp"

using namespace std;

// Struct to hold top scores and related metadata.
struct SCORELIST {
    int score[10];       // Array to store scores.
    char PLID[10][20];   // Array to store player IDs.
    char colcode[10][20]; // Array to store color codes.
    int ntries[10];      // Array to store number of tries.
    char mode[10][20];   // Array to store game modes.
    int n_scores;        // Number of scores stored.
};

// Check if a player has an active game.
int playerISPlaying(string PLID);

// Check if a player is allowed to play.
int canPlay(string PLID);

// Create a new game file for a player.
void createGame(vector<string> arguments , string mode);

// End the game for a player and update the related files.
void endGame(string PLID , string status); 

// Extract an argument by index from a space-separated string.
string getArgument(string arguments, int index);

// Retrieve the secret code for a player.
void getSecretCode(string PLID, string* secret_code);

// Retrieve the game's start time for a player.
void getGameTime(string PLID, string* game_time);

// Retrieve the maximum allotted time for a game.
void getMaxTime(string PLID, string* max_time);

// Calculate the remaining seconds in a game.
void secondsRemaining(string PLID, string* seconds);

// Retrieve all trials and the number of trials for a player.
void getTrials(string PLID, string* trials , string *num_trials);

// Check if a trial is a duplicate.
int isDup(string PLID, vector<string> content);

// Verify the validity of a trial number.
int checkTrial(string PLID, string trial);  

// Calculate the score based on game parameters.
int score(int max_time , int game_time , int num_trials);

// Retrieve the game mode for a player.
void getMode(string PLID, string* mode);

// Compare the player's trial against the secret code.
void compare_code(string secret_code, string trial, int *corrects, int *wrongs);

// Process a player's trial and update the game state.
void try_command(string PLID , vector<string> colors, string numberTry, string* status, string* data);

// Find the top scores and populate the SCORELIST struct.
int findTopScores(SCORELIST *list);

// Sort the scores in descending order.
void sortScores(SCORELIST &list);

// Finds the most recent game file for a specific player.
bool FindLastGame(string PLID, string *fname);

// Retrieves game data from a specific game file and counts the trials.
int getGame(string game, string *data);

#endif
