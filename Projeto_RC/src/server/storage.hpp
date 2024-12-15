
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




void updateGame(string PLID, vector<string> arguments);

void updateScoreboard(string PLID, vector<string> arguments);

int try_command(vector<string> arguments);
#endif




