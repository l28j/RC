
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
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    namespace fs = std::filesystem;

    if (!fs::exists(path)){
        return 0;
    }

    string time_remaining = "";

    secondsRemaining(PLID, &time_remaining);
    printf("Time remaining: %s\n", time_remaining.c_str());
    if (stoi(time_remaining) <= 0){
        return 0;
    }

    return 1;
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

        string score_path = score_dir + "_" + PLID + to_string(nowLocal->tm_mday) + "_" + to_string(nowLocal->tm_mon) + "_" + to_string(nowLocal->tm_year)
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

string getArgument(string arguments, int index) {
    // Split the arguments string into a vector of strings
    vector<string> args;
    stringstream ss(arguments);
    string arg;
    while (getline(ss, arg, ' ')) {
        args.push_back(arg);
    }

    // Return the argument at the specified index
    if (index < 0 || index >= static_cast<int>(args.size())) {
        return "";
    }
    return args[index];
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

    string secret_code_str = getArgument(first_line, 2);

    if (secret_code_str == "") {
        throw runtime_error("Failed to find the third argument in the first line");
    }

    *secret_code = secret_code_str;

}

void getGameTime(string PLID, string* game_time) {
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

    // Processar a linha para extrair o quarto argumento (tempo de jogo)
    string game_time_str = getArgument(first_line, 4);
    string full_time_str = getArgument(first_line, 5);

    if (game_time_str == "" || full_time_str == "") {
        throw runtime_error("Failed to find the fourth and fifth arguments in the first line");
    }

    *game_time = game_time_str + " " + full_time_str;
}

void getMaxTime(string PLID, string* max_time) {
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

    string max_time_str = getArgument(first_line, 3);

    if (max_time_str == "") {
        throw runtime_error("Failed to find the second argument in the first line");
    }

    *max_time = max_time_str;

}

void secondsRemaining(string PLID, string* seconds) {
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

    string max_time_str = getArgument(first_line, 3);   
    string full_time_str = getArgument(first_line, 6);

    if (max_time_str == "" || full_time_str == "") {
        throw runtime_error("Failed to find the fourth and fifth arguments in the first line");
    }

    // Obter o tempo atual
    time_t now = time(NULL);
    printf("Now: %ld\n", now);
    printf("Full time: %s\n", full_time_str.c_str());
    printf("Max time: %s\n", max_time_str.c_str());
    // Calcular o tempo restante
    int remaining = stoi(max_time_str) - (now - stoi(full_time_str));
    
    *seconds = to_string(remaining);
}

void getTrials(string PLID, string *trials , string *num_trials){
    // Construir o caminho para o arquivo
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    Fs file = Fs(path);

    // Abrir o arquivo
    int error = file.open(READ);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    string data = "";
    
    // Ler o arquivo
    error = file.read(&data);
    if (error < 0) {
        throw runtime_error("Failed to read from file");
    }

    // Fechar o arquivo
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }

    // Ignorar a primeira linha
    size_t pos = data.find("\n");
    if (pos == string::npos) {
        throw runtime_error("Failed to find the first newline character");
    }
    data = data.substr(pos + 1);
    string temp = data;

    // Contar o número de tentativas
    int count = 0;
    pos = temp.find("\n");
    while (pos != string::npos) {
        count++;
        temp = temp.substr(pos + 1);
        pos = temp.find("\n");
    }

    *trials = data;
    *num_trials = to_string(count); 
}
