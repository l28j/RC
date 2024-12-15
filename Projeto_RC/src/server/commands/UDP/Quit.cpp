
#include "Quit.hpp"


Quit::Quit(vector<string> args){
    this->socketType = "UDP";
    this->returnCode = RQT;

    this->PLID = args[0];

    if (!Verify::isUID(this->PLID)){
        printf("Invalid PLID\n");
        this->status = ERR;
    }
}   


void Quit::execute(){

    //Verify if the arguments are valid
    if (this->status == ERR){
        this->send(this->status);
        return;
    }

    //Verify if the PLID is already in use
    if (playerISPlaying(this->PLID) == 0){
        this->status = NOK;
        this->send(this->status);
        return;
    }
    string secret_code = "";
    getSecretCode(this->PLID, &secret_code);

    // Separete the secret code in 4 parts
    string secret_code_parts;
    for (int i = 0; i < 4; i++){
        secret_code_parts += secret_code[i];
        if (i != 3){
            secret_code_parts += " ";
        }
    }
    endGame(this->PLID, "Q");
    this->status = OK;
    this->send(status + " " + secret_code_parts);
}