#ifndef COMMON_FS_HPP
#define COMMON_FS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm> 

using namespace std;

// Modes for file operations
#define READ 1
#define WRITE 2

class Fs {
    public:
        // Constructor: Initializes the file system object with a file path.
        Fs(string path) : path(path) {};

        // Writes data to the file.
        int write(string* data);

        // Reads all data from the file.
        int read(string* data);

        // Renames the file to a new path.
        int rename(string* newPath);

        // Gets the size of the file in bytes.
        int getSize();

        // Reads the first line of the file.
        int getFirstLine(string* data);

        // Checks if the file is currently open.
        bool isOpen();

        // Opens the file in the specified mode (READ or WRITE).
        int open(int mode);

        // Closes the file.
        int close();

        // Writes data to a new line in the file.
        int writeOnNewLine(string* data);

        // Returns the file path.
        string getPath();

    private:
        string path; // Path to the file.
        int fd = -1; // File descriptor (-1 indicates file is not open).
};

#endif
