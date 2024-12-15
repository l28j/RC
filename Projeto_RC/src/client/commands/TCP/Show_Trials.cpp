
#include "Show_Trials.hpp"


int Show_Trials::execute() {
    if (!this->client->isPlaying()) {
        printf("%s\n", string(NO_GAMES).c_str());
        return 0;
    }
    return Command::execute();
}

void Show_Trials::send() {
    string data = this->formatData();
    this->networkClient->sendData(data);
}

string Show_Trials::formatData() {
    return string(STR) + " " + this->client->getID() + "\n";
}

void Show_Trials::receive() {
    string data = this->networkClient->receiveData();

    Parser parser =  Parser(data);

    string command = parser.getCommand();
    vector<string> arguments = parser.getArgs();

    if (command == ERR || command != RST ) {
        printf("ENTREI1\n");
        throw ServerResponseError();
    }
    
    string status = arguments[0];   
    printf("STATUS: %s\n", status.c_str());
    if (status == ACT || status == FIN) {
        string file_name = arguments[1];
        string file_size = arguments[2];
        string input = parser.getInput();
        size_t pos = input.find(file_size);
        string content_to_show = input.substr(pos + file_size.length() + 1);
        printf("%s\n", content_to_show.c_str());
        Fs file = Fs(file_name);
        file.open(WRITE);
        file.write(&content_to_show);
        file.close();
    }
    else if (status == NOK) {
        printf("%s\n", string(NO_GAMES).c_str());
    }
    else {
        printf("ENTREI2\n");
        throw ServerResponseError();
    }
}
   
