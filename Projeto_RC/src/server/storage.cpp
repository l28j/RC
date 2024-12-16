
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

    //Set new path 
    time_t full_time ;
    struct tm* nowLocal;
    string time_str = "";
    time(&full_time);

    string time_reamining = "";

    secondsRemaining(PLID, &time_reamining);
    
    nowLocal = gmtime(&full_time);
    nowLocal->tm_year += 1900;
    nowLocal->tm_mon += 1;

    string new_path = dir_path  
    + to_string(nowLocal->tm_year) + to_string(nowLocal->tm_mon) + to_string(nowLocal->tm_mday) + "_" 
    + to_string(nowLocal->tm_hour) + to_string(nowLocal->tm_min) + to_string(nowLocal->tm_sec) + "_"
    + status + ".txt";

    if (status == "W"){
        //Update the scoreboard
        string score_dir = "src/server/_SCORES/";
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

        string trials = "";

        string score_str = "";
        string max_time = "";
        string game_time = "";  
        string num_trials = "";
        string secret_code = "";  
        string game_mode = "";  

        getMaxTime(PLID, &max_time);
        getTrials(PLID, &trials, &num_trials);
        getSecretCode(PLID, &secret_code);
        getMode(PLID, &game_mode);
        game_time = to_string(stoi(max_time) - stoi(time_reamining));

        int score_int = score(stoi(max_time), stoi(game_time), stoi(num_trials));

        score_str = to_string(score_int);

        string data = "";
 
        data = score_str + " " + PLID + " " + secret_code + " " + num_trials + " " + game_mode + "\n";
        error = file.write(&data);

        if (error < 0){
            throw runtime_error("Failed to write to file");
        }

        error = file.close();

        if (error < 0){
            throw runtime_error("Failed to close file");
        }
    }

    Fs file = Fs("src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt");

 
    int error ;

    string max_time = "";
    getMaxTime(PLID, &max_time);
    int game_time = stoi(max_time) - stoi(time_reamining);
    string game_time_str = to_string(game_time);
    
    string end_line = to_string(nowLocal->tm_year) + "-" + to_string(nowLocal->tm_mon) + "-" + to_string(nowLocal->tm_mday) + " " 
                    + to_string(nowLocal->tm_hour) + ":" + to_string(nowLocal->tm_min) + ":" + to_string(nowLocal->tm_sec) + " " + game_time_str + " \n";

    error = file.open(WRITE);

    if (error < 0){
        throw runtime_error("Failed to open file");
    }

    error = file.writeOnNewLine(&end_line);
    
    if (error < 0){
        throw runtime_error("Failed to write to file");
    }

    error = file.close();

    if (error < 0){
        throw runtime_error("Failed to close file");
    }

    file.rename(&new_path); 
}


int score(int max_time , int game_time , int num_trials){
    return 100 *(0.4*((600 - max_time)/600) + 0.3*((max_time-game_time)/max_time) + 0.2*((8 - num_trials)/8));
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

void getMode(string PLID, string* mode) {
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

    string mode_str = getArgument(first_line, 1);

    if (mode_str == "") {
        throw runtime_error("Failed to find the second argument in the first line");
    }

    *mode = mode_str;

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

int canPlay(string PLID){
    //Build path to the file
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    namespace fs = std::filesystem;

    if (!fs::exists(path)){
        return 0;
    }

    string time_remaining = "";

    secondsRemaining(PLID, &time_remaining);
    
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

int isDup(string PLID, vector<string> content){
    
    string trials = "";
    string num_trials = "";

    getTrials(PLID, &trials, &num_trials);

    if (stoi(num_trials) == 0){
        return 0;
    }
    
    // Encontrar a posição do último '\n'
    size_t last_pos = trials.rfind("\n"); // Posição do último '\n'
    if (last_pos == std::string::npos) {
        throw std::runtime_error("Failed to find the last newline character");
    }
    
    //Extrair a última linha (após o último '\n')
    std::string last_trial_line = trials.substr(last_pos + 1);

    // Validar o conteúdo da última linha
    if (last_trial_line.empty()) {
        return 0;
    }

    // Concatenar os elementos do vetor content
    std::string combined_content = content[0] + content[1] + content[2] + content[3];

    // Verificar se a última linha corresponde ao conteúdo esperado
    if (last_trial_line == combined_content) {
        return 1;
    }

    return 0;
}

int checkTrial(string PLID, string trial){
    string trials = "";
    string num_trials = "";

    getTrials(PLID, &trials, &num_trials);

    if (stoi(trial) == stoi(num_trials) + 1){
        return 1;
    }

    return 0;

}

void compare_code(string secret_code, string trial, int *corrects, int *wrongs) {
    *corrects = 0;
    *wrongs = 0;

    vector<bool> matched_secret(4, false); 
    vector<bool> matched_trial(4, false); 

    for (int i = 0; i < 4; i++) {
        if (secret_code[i] == trial[i]) {
            (*corrects)++;
            matched_secret[i] = true;
            matched_trial[i] = true;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (!matched_trial[i]) { 
            for (int j = 0; j < 4; j++) {
                if (!matched_secret[j] && trial[i] == secret_code[j]) { 
                    (*wrongs)++;
                    matched_secret[j] = true; 
                    break;
                }
            }
        }
    }
}

void try_command(string PLID , vector<string> colors, string numberTry, string* status, string* data){
    string secret_code = "";
    string end_code = "";
    getSecretCode(PLID, &secret_code);

    if (secret_code == ""){
        throw runtime_error("Failed to get secret code");
    }

    string str_content = colors[0] + colors[1] + colors[2] + colors[3];

    string corrects = "";
    string wrongs = "";

    int corrects_int = 0;
    int wrongs_int = 0;

    compare_code(secret_code, str_content, &corrects_int, &wrongs_int);

    corrects = to_string(corrects_int);
    wrongs = to_string(wrongs_int);

    if (corrects_int != 4 && numberTry == "8"){
        printf("corrects_int: %d\n", corrects_int);
        printf("numberTry: %s\n", numberTry.c_str());
        *status = "ENT";
        end_code = "F"; 
    }
    else if(corrects_int == 4){
        *status = "OK";
        end_code = "W";
    }
    else{
        *status = "OK";
    }
        
    string time_remaining = "";
    string max_time = "";
    
    secondsRemaining(PLID, &time_remaining);
    getMaxTime(PLID, &max_time);

    string seconds = to_string(stoi(max_time) - stoi(time_remaining));

    string trial = "T: " + str_content + " " + corrects + " " + wrongs + " " + seconds;

    //Build path to the file
    string path = "src/server/_GAMES/" + string("GAME") + "_" + PLID + ".txt";

    Fs file = Fs(path);

    // Abrir o arquivo
    int error = file.open(WRITE);
    if (error < 0) {
        throw runtime_error("Failed to open file");
    }

    // Escrever a tentativa no arquivo
    error = file.writeOnNewLine(&trial);
    if (error < 0) {
        throw runtime_error("Failed to write to file");
    }

    // Fechar o arquivo
    error = file.close();
    if (error < 0) {
        throw runtime_error("Failed to close file");
    }
    *data = "";  

    if (*status == "OK") {
        *data = numberTry + " " + corrects + " " + wrongs;
    } else {
        for (int i = 0; i < 4; i++) {
            *data +=  std::string(1, secret_code[i]) + " ";
        }
    }

    if (end_code != ""){
        endGame(PLID, end_code);
    }
    
}





    