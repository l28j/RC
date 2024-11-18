#include "showasset.hpp"

void ShowAsset::send(){
    string data = formatData();

    this->networkClient->sendData(data);
}

void ShowAsset::receive(){
    string data = this->networkClient->receiveData();

    Parser parser = Parser(data);

    string command = parser.getCommand();
    vector<string> args = parser.getArgs();

    if(command != TCP_SHOW_ASSET_RESPONSE || args.size() < 1) {
        throw ServerResponseError();
    }

    string status = args[0];

    if(status == STATUS_OK){
        string fileName = args[1];
        string fileSize = args[2];

        printf("Asset %s: %s has %s bytes\n", this->assetId.c_str(), fileName.c_str(), fileSize.c_str());

        args.erase(args.begin(), args.begin() + 3);

        saveFile(fileName, &args);

        printf("%s\n", string(SHOW_ASSET_SUCCESS).c_str());

    }
    else if(status == STATUS_NOK){
        printf("%s\n", string(SHOW_ASSET_FAILURE).c_str());
    }
    else {
        throw ServerResponseError();
    
    }
}

string ShowAsset::formatData() {
    return string(TCP_SHOW_ASSET_COMMAND) + " " + assetId + "\n";
}

/**
 * Saves file to disk
 * @param fileName name of file to be saved
 * @param fileData pointer to vector of strings containing file data
 */
void ShowAsset::saveFile(string fileName, vector<string>* fileData) {
    Fs fs = Fs(fileName);

    // join vector into string
    // string was split into vector in parser.cpp using spaces as delimiters
    string fileDataString = "";

    for(size_t i = 0; i < fileData->size(); i++) {
        if(i == fileData->size() - 1) {
            fileDataString.append(fileData->at(i));
            
        }else {
            fileDataString.append(fileData->at(i) + " ");
        }
    }

    if(fs.open(WRITE) == -1) {
        throw FsWriteError();
    }

    if(fs.write(&fileDataString) == -1) {
        throw FsWriteError();
    }

    if(fs.close() == -1) {
        throw FsWriteError();
    }
}