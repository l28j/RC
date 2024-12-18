
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


struct SCORELIST {
    int score[10];
    char PLID[10][20];
    char colcode[10][20];
    int ntries[10];
    char mode[10][20];
    int n_scores;
};

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

int score(int max_time , int game_time , int num_trials);

void getMode(string PLID, string* mode) ;

void compare_code(string secret_code, string trial, int *corrects, int *wrongs);

void try_command(string PLID , vector<string> colors, string numberTry, string* status, string* data);

int findTopScores(SCORELIST *list);

void sortScores(SCORELIST &list);

#endif




