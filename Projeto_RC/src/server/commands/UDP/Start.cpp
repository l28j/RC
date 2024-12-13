#include "Start.hpp"

#include <algorithm>  
#include <iostream>
#include <ctime>
#include <cstdio>
#include <random> 

Start::Start(vector<string> args){
  this->socketType = "UDP";
  this->returnCode = RSG;

  this->PLID = args[0];
  this->timeStr = args[1]; 

  if (!Verify::isUID(this->PLID) || !Verify::isNumber(this->timeStr) 
      || stoi(this->timeStr) < 0 || stoi(this->timeStr) > MAX_TIME){
    this->status = ERR;
  }
}

void Start::execute(){

  //Verify if the arguments are valid
  if (this->status == ERR){
    this->send(this->status);
    return;
  }

  //Verify if the PLID is already in use

  if (playerISPlaying(this->PLID) == 1){
    if(!canPlay(this->PLID)){
      endGame(this->PLID, "L");
    }
    this->status = NOK;
    this->send(this->status);

    return;
  }


  string code = "";
  vector<string> colors = { RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE };

  //Select 4 random colors

  random_device rd; 
  default_random_engine rng(rd());
  shuffle(colors.begin(), colors.end(), rng);

  for (int i = 0; i < 4; i++){
    code += colors[i];
  }

  string max_time = this->timeStr;

  time_t full_time ;
  string full_time_str = "";
 
  struct tm* nowLocal;
  string time_str = "";
 
  time(&full_time);
  full_time_str = to_string(full_time);
  nowLocal = gmtime(&full_time);
  time_str = to_string(nowLocal->tm_year + 1900) + "-" + to_string(nowLocal->tm_mon + 1) +
             "-" + to_string(nowLocal->tm_mday) + " "
            + to_string(nowLocal->tm_hour) + ":" + to_string(nowLocal->tm_min) + ":" + to_string(nowLocal->tm_sec);

  vector<string> arguments = { this->PLID, code, max_time, time_str, full_time_str};


  try{
    createGame(arguments, "P") ;
  } catch (const runtime_error& e){
    this->returnCode = "ERR";
    this->send(this->status); 
    return;
  }

  this->status = OK;
  this->send(this->status);

  return;
}








  



 