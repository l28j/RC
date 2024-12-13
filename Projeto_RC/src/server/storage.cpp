
#include "storage.hpp"
#include <string>
#include <filesystem>

void createGame(vector<string> arguments, string mode){

    string dir_path = "src/server/_GAMES";

    namespace fs = std::filesystem;

    if (!fs::exists(dir_path)){
        fs::create_directory(dir_path);
    }

    //Build path to the file
    string path = dir_path + "/" + string("GAME") + "_" + arguments[0] + ".txt";

    Fs file  = Fs(path);
    
    int error = file.open(WRITE);

    if (error < 0){
        printf("Failed to open file\n");
        throw runtime_error("Failed to open file");
    }

    //Write the game to the file
    string data = arguments[0] + " " + mode + " " + arguments[1] + " " + arguments [2] + " " 
                + arguments[3] + " " + arguments[4] + " " + " \n"; 


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
    string dir_path = "src/server/_GAMES";

    string path = dir_path + "/" + string("GAME") + "_" + PLID + ".txt";

    //verify if the file exists
    namespace fs = std::filesystem;

    if (!fs::exists(path)){
        return 1;
    }

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
        return 1;
    }
    else{
        return 0;
    }
}

int playerISPlaying(string PLID){
    //Build path to the file
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    namespace fs = std::filesystem;

    if (!fs::exists(path)){
        return 0;
    }

    return 1;
}

void endGame(string PLID, string status){
    
    //Create Dir to this client

    string dir_path = "src/server/_GAMES/" + PLID + "/";

    namespace fs = std::filesystem;
    if (!fs::exists(dir_path)){
        fs::create_directory(dir_path);
        if (!fs::exists(dir_path)){
            throw runtime_error("Failed to create directory");
        }
    }

    //End game and move it to the client dir

    time_t full_time ;
    struct tm* nowLocal;
    string time_str = "";
    time(&full_time);
    
    nowLocal = gmtime(&full_time);
    nowLocal->tm_year += 1900;
    nowLocal->tm_mon += 1;

    string new_path = dir_path  
    + to_string(nowLocal->tm_year) + to_string(nowLocal->tm_mon) + to_string(nowLocal->tm_mday) + "_" 
    + to_string(nowLocal->tm_hour) + to_string(nowLocal->tm_min) + to_string(nowLocal->tm_sec) + "_"
    + status + ".txt";

    //Move the file

    Fs file = Fs("src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt");

    int error = file.rename(&new_path); 

    if (error < 0){
        throw runtime_error("Failed to move file");
    }   

    
    if (status == "W"){
        //Update the scoreboard
        string score_dir = "src/server/_SCORES";
        if (!fs::exists(score_dir)){
            fs::create_directory(score_dir);
        }

        string score_path = score_dir + "_" + PLID + to_string(nowLocal->tm_year) + to_string(nowLocal->tm_mon) + to_string(nowLocal->tm_mday) 
                            + "_" + to_string(nowLocal->tm_hour) + to_string(nowLocal->tm_min) + to_string(nowLocal->tm_sec) + ".txt";
        
        Fs file = Fs(score_path);

        int error = file.open(WRITE);

        if (error < 0){
            throw runtime_error("Failed to open file");
        }

        string data = PLID + " \n";

        error = file.write(&data);

        if (error < 0){
            throw runtime_error("Failed to write to file");
        }

        error = file.close();

        if (error < 0){
            throw runtime_error("Failed to close file");
        }
    }
}

void getSecretCode(string PLID, string* secret_code) {
    // Construir o caminho para o arquivo
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    Fs file = Fs(path);

    // Abrir o arquivo
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string first_line = "";

    // Ler a primeira linha do arquivo
    error = file.getFirstLine(&first_line);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Fechar o arquivo
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Processar a linha para extrair o terceiro argumento (CCCC)
    std::istringstream iss(first_line);
    std::string token;
    int space_count = 0;

    while (iss >> token) {
        space_count++;
        if (space_count == 3) { // Terceiro argumento após o segundo espaço
            *secret_code = token;
            return;
        }
    }

    // Caso não encontre o terceiro argumento, lança uma exceção
    throw runtime_error("Failed to find the third argument in the first line");
}



/*
int end_game(string PLID, string status, string score){
    //arguments=<PLID, end_date, end_time, start_time, result(code)>


    std::string filepath = "src/server/GAMES/" + string("GAME") + "_" + PLID + ".txt";
    
    std::string buffer="";

    time_t full_time ;
    struct tm* nowLocal;
    string time_str = "";
    time(&full_time);
    
    nowLocal = gmtime(&full_time);
    nowLocal->tm_year += 1900;
    nowLocal->tm_mon += 1;


    Fs file = Fs(filepath);

    int error = file.open(WRITE);
    if (error < 0){
        throw runtime_error("Failed to open file");
    }

    buffer = std::string("\n") + to_string(nowLocal->tm_year) + to_string(nowLocal->tm_mon) + to_string(nowLocal->tm_mday) + " " 
    + to_string(nowLocal->tm_hour) + to_string(nowLocal->tm_min) + to_string(nowLocal->tm_sec) + score;

    error = file.writeOnNewLine(&buffer);
    if (error < 0){
        throw runtime_error("Failed to write to file");
    }

    error = file.close();
    if(error < 0){
        throw runtime_error("Failed to close to file");
    }

    string dir_path = "src/server/GAMES/" + PLID + "/";
    string new_path = dir_path  
    + to_string(nowLocal->tm_year) + to_string(nowLocal->tm_mon) + to_string(nowLocal->tm_mday) + "_" 
    + to_string(nowLocal->tm_hour) + to_string(nowLocal->tm_min) + to_string(nowLocal->tm_sec) + "_"
    + status + ".txt";



    Fs directory = Fs(dir_path);

    error = directory.createDirectory();
    if(error < 0){
        throw runtime_error("Failed to create Directory");
    }

    //Passo redundante?
    
    Fs newfile = Fs(newpath);
    error = newfile.createFile();
    if(error < 0){
        throw runtime_error("Failed to Create Destinationn File");
    }

    error = file.rename(&new_path);
    if(error < 0){
        throw runtime_error("Failed to move file");
    }



    return 0;
}*/
