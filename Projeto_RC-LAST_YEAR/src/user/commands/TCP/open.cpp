#include "open.hpp"
 
int Open::execute() {
    // check if user is logged in
    if(!this->clientState->isLoggedIn()) {
        printf("%s\n", string(NOT_LOGGED_IN).c_str());
        return 0;
    }
    
    return Command::execute();
}

void Open::send() {
    string data = this->formatData();

    this->networkClient->sendData(data);
}

void Open::receive() {
    string data = this->networkClient->receiveData();

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != TCP_OPEN_RESPONSE || args.size() < 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK) {
        string auctionId = args[1];

        printf("Auction %s opened\n", auctionId.c_str());
    }
    else if(status == STATUS_NOK) {
        printf("%s\n", string(OPEN_FAILURE).c_str());
    }
    else if(status == STATUS_NOT_LOGGED_IN) {
        printf("%s\n", string(NOT_LOGGED_IN).c_str());
    }
    else {
        throw ServerResponseError();
    }

}

string Open::formatData() {
    string userId = this->clientState->getUser();
    string password = this->clientState->getPassword();

    int fSize = getFileSize();

    string fileSize = to_string(fSize);

    string fileData = getFileData();

    return string(TCP_OPEN_COMMAND) + " " + userId + " " + password + " " + this->name + " " + this->startValue + " " + this->timeActive + " " + this->fileName + " " + fileSize + " " + fileData + "\n";
}

/**
 * Gets file size specified in input
 * @return file size in bytes
 */
int Open::getFileSize() {
    Fs fs = Fs(this->fileName);

    if(fs.open(READ) == -1) {
        throw FsReadError();
    }

    int size = fs.getSize();

    if(size == -1) {
        throw FsReadError();
    }

    if(fs.close() == -1) {
        throw FsReadError();
    }

    if(size > MAX_FILE_SIZE) {
       throw FileSizeError();
    }

    return size;
}

/**
 * Gets file data specified in input
 * @return file data
 */
string Open::getFileData() {
    Fs fs = Fs(this->fileName);

    // create pointer to string
    string data = "";

    if(fs.open(READ) == -1) {
        throw FsReadError();
    }

    if(fs.read(&data) == -1) {
        throw FsReadError();
    }

    if(fs.close() == -1) {
        throw FsReadError();
    }

    return data;
}