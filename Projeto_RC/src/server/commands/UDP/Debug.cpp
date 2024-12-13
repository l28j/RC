
#include "Debug.hpp"


Debug::Debug(vector<string> args){
    printf("Debug command\n");
    this->socketType = "UDP";
    this->returnCode = RDB;

    this->PLID = args[0];
    this->timeStr = args[1]; 
    this->code = "" ;
    for (std::size_t i = 2; i < args.size(); i++) {
        this->code += args[i];
    }

    if (!Verify::isUID(this->PLID) || !Verify::isNumber(this->timeStr) 
      || stoi(this->timeStr) < 0 || stoi(this->timeStr) > MAX_TIME){
        this->status = ERR;
    }
    for (int i = 0; i < 4; i++){
        if (!Verify::isColor(this->code.substr(i, 1))){
            this->status = ERR;
        }
    }
}

void Debug::execute(){

    //Verify if the arguments are valid
    if (this->status == ERR){
        this->send(this->status);
        return;
    }

    //Verify if the PLID is already in use

    if (playerISPlaying(this->PLID) == 1){
        this->status = NOK;
        this->send(this->status);
        return;
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
        createGame(arguments, "D");
    }
    catch (const runtime_error& e){
        this->status = ERR;
        this->send(this->status);
        return;
    }

    this->status = OK;
    this->send(this->status);    
}
