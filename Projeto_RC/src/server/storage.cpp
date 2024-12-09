
#include "storage.hpp"
#include <string>


void createGame(vector<string> arguments){
    //Build path to the file
    string path = "_GAMES/" + string("GAME") + "_" + arguments[0] + ".txt";

    Fs file  = Fs(path);
    
    int error = file.open(WRITE);

    if (error < 0){
        printf("Failed to open file\n");
        throw runtime_error("Failed to open file");
    }

    //Write the game to the file
    string data = arguments[0] + " " + arguments[1] + " " + arguments [2] + " " 
                + arguments[3] + " " + arguments[4] + " " + arguments[5] + " \n"; 


    error = file.write(&data);

    if (error < 0){
        printf("Failed to write to file\n");
        throw runtime_error("Failed to write to file");
    }

    error = file.close();

    if (error < 0){
        printf("Failed to close file\n");
        throw runtime_error("Failed to close file");
    }
}

int canPlay(string PLID){
    //Build path to the file
    string path = "_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    Fs file  = Fs(path);


    string first_line = "";
    vector<string> arguments;
    string time_to_play = "";
    string start_time = ""; 

    int error = file.open(READ);

    if (error < 0){
        throw runtime_error("Failed to open file");
    }

    error = file.getFirstLine(&first_line);

    if (error < 0){
        throw runtime_error("Failed to read from file");
    }

    error = file.close();

    if (error < 0){
        throw runtime_error("Failed to close file");
    }

    std::istringstream iss(first_line);
    std::string token;
    while (iss >> token) {
        arguments.push_back(token);
    }

    time_to_play = arguments[3];
    start_time = arguments[6];

    //Get current time
    time_t now = time(NULL);

    //Check if the player can play

    if (stoi(time_to_play) > (now - stoi(start_time))){
        return 0;
    }
    else{
        return -1;
    }
}

int playerISPlaying(string PLID){
    //Build path to the file
    string path = "GAMES/" + string("GAME") + "_" + PLID + ".txt";

    Fs file  = Fs(path);

    if (file.isOpen()){
        return 0;
    }
    else{
        return -1;
    }
}



    
    