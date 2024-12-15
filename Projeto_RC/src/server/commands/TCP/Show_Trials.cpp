
#include "Show_Trials.hpp"

Show_Trials::Show_Trials(vector<string> args){
    this->socketType = "TCP";
    this->returnCode = RST;

    this->PLID = args[0];

    if (!Verify::isUID(this->PLID)){
        this->status = ERR;
    }
}

void Show_Trials::execute(){

    //Verify if the arguments are valid
    if (this->status == ERR){
        this->send(this->status);
        return;
    }

    //Verify if the PLID is already in use

    if (!playerISPlaying(this->PLID)){
        this->status = FIN;
        this->send(this->status);
        return;
    }

    string file_name = "STATE_" + this->PLID + ".txt";

    string data = " ";

    data += "\t" + string("Active game found for player") + " " + this->PLID + "\n";
    
    data += "Game initiated:" + string(" ");

    //Get the start time of the game
    string path = "src/server/_GAMES/" + string("GAME") + "_" + this->PLID + ".txt";

    Fs file = Fs(path);

    int error = file.open(READ);

    if (error < 0){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to open file");
    }

    string max_time = "";
    string game_time = "";

    try {
        getMaxTime(this->PLID, &max_time);
        getGameTime(this->PLID, &game_time);
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get game time or max time");
    }

    data += game_time + " " + "with" + " " + max_time + " " + "seconds to be completed\n";
    data += "\n";

    string num_trials = "";
    string trials = "";

    try {
        getTrials(this->PLID, &trials, &num_trials);
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get trials");
    }

    data += "\t" + string("--- ") + "Transactions found: " + num_trials + " ---\n";
    data += "\n";
    data += trials;

    string time_remaining = "";

    try {
        secondsRemaining(this->PLID, &time_remaining);
    } catch (const runtime_error& e){
        this->status = NOK;
        this->send(this->status);
        throw runtime_error("Failed to get time remaining");
    }

    data += "\n";
    data += " -- " + time_remaining + " " + "seconds remaining to be completed --\n";
    
    string file_size = to_string(data.length());

    this->status = ACT;
    this->send(this->status + " " + file_name + " " + file_size + " " + data);
}










