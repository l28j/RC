#ifndef CLIENT_SHOW_ASSET_H
#define CLIENT_SHOW_ASSET_H

#include "../command.hpp"

class ShowAsset : public Command {
    public:
        ShowAsset(string assetId): Command(TCP, SHOW_ASSET), assetId(assetId) {};
        void send();
        void receive();
        string formatData();

        void saveFile(string fileName, vector<string>* fileData);

    private:
        string assetId;
};

#endif