#ifndef USER_OPEN_COMMAND_H
#define USER_OPEN_COMMAND_H

#include "../command.hpp"

class Open: public Command {
    public:
        Open(string name, string startValue, string timeActive, string fileName):
            Command(TCP, OPEN), name(name), startValue(startValue), timeActive(timeActive), fileName(fileName) 
        {}

        int execute() override;
        
        void send();
        void receive();
        string formatData();

    private:
        string getFileData();

        int getFileSize();

        string name;
        string startValue;
        string timeActive;

        string fileName;
};

#endif