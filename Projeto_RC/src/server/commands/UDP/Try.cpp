
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
}

void Try::execute(){

  //check sytax of message
  int i=0, j=0;
  bool check=false;
  std::vector<std::string> code = {"R", "G", "B", "Y", "O", "P"};
  for(i=0; i<4; i++){
    for(j=0; j<6; j++){
      if(this->content[i]==code[j]){
        check=true;
        break;
      }
    }
    if(check==false){
      this->status=ERR;
      this->send(this->status);
      return;
    }
    check=false;
  }

  if (!Verify::isUID(this->PLID) || !Verify::isNumber(this->numberTry) 
      || stoi(this->numberTry) < 0){
    this->status = ERR;
    return;
  }

  if (this->status == ERR){
    this->send(this->status);
    return;
  }

  //Verify if the PLID is has a game open.

  if (playerISPlaying(this->PLID) == 1){
    if(!canPlay(this->PLID)){
      endGame(this->PLID, "T");
      this->status = ETM;
      this->send(this->status);
      return;
    }
  }
  else{
    this->status = NOK;
    this->send(this->status);
    return;
  }
    //Make sure the play is new (trial is different, +1) or DUP
  vector<int> verification = verify_code(this->PLID, this->content, this->numberTry);
  if(verification[0]==0){
    this->status=INV;
    send(this->status);
    return;
  }
  else if(verification[0]==2){
    printf("DUPLICATED \n");
    fflush(stdout);
    this->status=DUP;
    send(this->status);
    return;
  }

  string str_content = this->content[0] + this->content[1] + this->content[2] + this->content[3];
  vector<string> result = check_try(this->PLID, this->content, this->numberTry);
  vector<string> arguments = {this->PLID, str_content ,result[1], result[2], std::to_string(verification[1])};
  if(stoi(result[0])==1){
    try{ try_command(arguments);
    } catch (const runtime_error& e){
    this->returnCode = "ERR";
    this->send(this->status); 
    return;
    }
    endGame(this->PLID, "W");
    printf("WIN \n");
    fflush(stdout);
    this->status=OK;
    send(this->status);
    return;
  }
  else if(stoi(result[0])==-1){
    try{ try_command(arguments);
    } catch (const runtime_error& e){
      this->returnCode = "ERR";
      this->send(this->status); 
      return;
    }
    endGame(this->PLID, "L");
    printf("LOSS\n");
    fflush(stdout);
    this->status=ENT;
    send(this->status);
    return;
  }

  try{try_command(arguments);
  } catch (const runtime_error& e){
    this->returnCode = "ERR";
    this->send(this->status); 
    return;
  }

  printf("OK \n");
  fflush(stdout);

  this->status=OK;
  send(this->status);
  return;
}
