
#include "Try.hpp"

#include <algorithm>  
#include <iostream>
#include <ctime>
#include <cstdio>
#include <random> 

Try::Try(vector<string> args){
  this->socketType = "UDP";
  this->returnCode = RTR;

  this->PLID = args[0];
  int i=0;
  this->content.resize(4);
  for(i=0; i<4; i++){
    this->content[i]=args[i+1];
  }
  this->numberTry = args[5]; 

  //Check arguments
  if(!(Verify::isUID(this->PLID) && Verify::isNumber(this->numberTry) && stoi(this->numberTry) >= 0)){
    this->status = ERR;
  }
  for (i=0; i<4; i++){
    if(!(Verify::isColor(this->content[i]))){
      this->status = ERR;
    }
  }
  if (stoi(this->numberTry) > 8 || stoi(this->numberTry) < 0){
    this->status = INV;
  }
}

void Try::execute(){

    //Verify if the arguments are valid
    if ((this->status == ERR) || (this->status == INV)){
      this->send(this->status);
      return;
    }
    
    //Verify if the PLID is has a game open.
    if (!playerISPlaying(this->PLID)){
      this->status=NOK;
      send(this->status);
      return;
    }

    //Verify if the PLID can play
    if (!canPlay(this->PLID)){
      this->status=ETM;
      string secret_code = "";
      getSecretCode(this->PLID, &secret_code);
      for (int i = 0; i < 4; i++){
        this->status +=  " " + std::string(1, secret_code[i]);
      }
      send(this->status);
      endGame(this->PLID, "T");
      return;
    }

    if(isDup(this->PLID, this->content)){
      this->status=DUP;
      send(this->status);
      return;
    }

    if (!checkTrial(this->PLID, this->numberTry)){
      this->status=INV;
      send(this->status);
      return;
    }

    string status = "";
    string data = "";
    try_command(this->PLID, this->content, this->numberTry, &status, &data);

    this->status = status;
    this->send(this->status + " " + data);
}

    

    









