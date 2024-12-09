
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

void createGame(vector<string> arguments);

void endGame(string PLID);  

void updateGame(string PLID, vector<string> arguments);

void updateScoreboard(string PLID, vector<string> arguments);

#endif




