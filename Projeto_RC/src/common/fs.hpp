#ifndef COMMON_FS_HPP
#define COMMON_FS_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm> 
using namespace std;

// File operation modes
#define READ 1
#define WRITE 2

/**
 * @brief Class for file system operations.
 */
class Fs {
    public:
        /**
         * @brief Constructor to initialize file path.
         * @param path Path to the file.
         */
        Fs(string path): path(path) {};

        /**
         * @brief Writes data to the file.
         * @param data Pointer to the string to be written.
         * @return int 0 if success, -1 if error.
         */
        int write(string* data);

        /**
         * @brief Reads data from the file.
         * @param data Pointer to the string to store the read data.
         * @return int 0 if success, -1 if error.
         */
        int read(string* data);

        /**
         * @brief Renames the file to a new path.
         * @param newPath Pointer to the new path.
         * @return int 0 if success, -1 if error.
         */
        int rename(string* newPath);

        /**
         * @brief Gets the size of the file in bytes.
         * @return int Size of the file or -1 if error.
         */
        int getSize();

        /**
         * @brief Reads the first line of the file.
         * @param data Pointer to the string to store the first line.
         * @return int 0 if success, -1 if error.
         */
        int getFirstLine(string* data);

        /**
         * @brief Checks if the file is open.
         * @return true if open, false otherwise.
         */
        bool isOpen();

        /**
         * @brief Opens the file.
         * @param mode READ or WRITE mode.
         * @return int 0 if success, -1 if error.
         */
        int open(int mode);

        /**
         * @brief Closes the file.
         * @return int 0 if success, -1 if error.
         */
        int close();

        /**
         * @brief Writes data to the file on a new line.
         * @param data Pointer to the string to be written.
         * @return int 0 if success, -1 if error.
         */
        int writeOnNewLine(string* data);

        /**
         * @brief Gets the file path.
         * @return string Path to the file.
         */
        string getPath();

        /**
         * @brief Reads the last line of the file.
         * @param data Pointer to the string to store the last line.
         * @return int 0 if success, -1 if error.
         */
        int getLastLine(string* data);

    private:
        string path;  // Path to the file.
        int fd = -1;  // File descriptor, -1 if not open.
};

#endif
