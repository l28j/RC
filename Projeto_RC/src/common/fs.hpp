#ifndef COMMON_FS_HPP
#define COMMON_FS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

#define READ 1
#define WRITE 2


class Fs {
    public:
        Fs(string path): path(path) {};

        int write(string* data);

        int read(string* data);

        int rename(string* newPath);

        int getSize();

        int getFirstLine(string* data);

        int getLastLine(string* data);

        int getNumberOfTrials(int* trialCount);
        
        bool isOpen();

        int open(int mode);
        int close();

        int writeOnNewLine(string* data);

        string getPath();


    private:
        string path;

        int fd = -1;

};

#endif