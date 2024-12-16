
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

using namespace std;

int playerISPlaying(string PLID);

int canPlay(string PLID);

void createGame(vector<string> arguments , string mode);

void endGame(string PLID , string status); 

string getArgument(string arguments, int index);

void getSecretCode(string PLID, string* secret_code);

void getGameTime(string PLID, string* game_time);

void getMaxTime(string PLID, string* max_time);

void secondsRemaining(string PLID, string* seconds);

void getTrials(string PLID, string* trials , string *num_trials);

int isDup(string PLID, vector<string> content);

int checkTrial(string PLID, string trial);  

void compare_code(string secret_code, string trial, int *corrects, int *wrongs);

void try_command(string PLID , vector<string> colors, string numberTry, string* status, string* data);

#endif




