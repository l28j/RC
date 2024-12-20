#include "fs.hpp"

#include <sys/stat.h>

// Gets the file path defined in the constructor
string Fs::getPath() {
    return this->path;
}

/**
 * @brief Opens the file defined in the constructor.
 * @param mode READ or WRITE
 * @return int 0 if success, -1 if error
 */
int Fs::open(int mode) {
    // Cannot open a file inside a folder without ensuring the folder exists
    if(mode == READ){
        this->fd = ::open(this->path.c_str(), O_RDONLY, 0644);
    }
    else if(mode == WRITE){
        this->fd = ::open(this->path.c_str(), O_WRONLY | O_CREAT, 0644);
    }
    else{
        return -1;
    }

    if(this->fd < 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief Closes the file defined in the constructor.
 * @return int 0 if success, -1 if error
 */
int Fs::close() {
    if(!isOpen() || ::close(this->fd) < 0) {
        return -1;
    }

    this->fd = -1;

    return 0;
}

/**
 * @brief Checks if the file defined in the constructor is open.
 * @return true if the file is open
 * @return false if the file is not open
 */
bool Fs::isOpen() {
    return this->fd != -1;
}

/**
 * @brief Writes data to the file defined in the constructor.
 * @param data string pointer to data to be written to the file
 * @return int 0 if success, -1 if error
 */
int Fs::write(string* data) {
    if(!isOpen()) {
        return -1;
    }
    
    if(::write(this->fd, data->c_str(), data->size()) < 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief Returns the size of the file in bytes.
 * @return int -1 if error, else file size in bytes
 */
int Fs::getSize() {
    if(!isOpen()) {
        return -1;
    }

    // Move file pointer to the beginning of the file
    lseek(this->fd, 0, SEEK_SET);

    size_t size = lseek(this->fd, 0, SEEK_END); // Calculate the file size

    // Reset file pointer to the beginning of the file
    lseek(this->fd, 0, SEEK_SET);

    return static_cast<int>(size);
}

/**
 * @brief Reads the first line of the file defined in the constructor.
 * @param data string pointer to store the first line of the file
 * @return int 0 if success, -1 if error
 */
int Fs::getFirstLine(string* data) {
    if(!isOpen()) {
        return -1;
    }

    int size = getSize();

    if(size <= 0) {
        return -1;
    }

    char buffer[size];

    // Set file pointer to the beginning of the file
    lseek(this->fd, 0, SEEK_SET);

    ssize_t bytesRead = ::read(this->fd, buffer, size);

    if(bytesRead < 0) {
        return -1;
    }

    string str(buffer, bytesRead);

    size_t pos = str.find("\n");

    if(pos == string::npos) {
        return -1;
    }

    *data = str.substr(0, pos); // Extract the first line

    return 0;
}


/**
 * @brief Reads the last line of the file.
 * @param data string pointer to store the last line of the file
 * @return int 0 if success, -1 if error
 **/
int Fs::getLastLine(string* data) {
    if (!isOpen()) {
        return -1;
    }

    int size = getSize();

    if (size <= 0) {
        return -1;
    }

    char buffer[size];

    // Set file pointer to the beginning of the file
    lseek(this->fd, 0, SEEK_SET);

    ssize_t bytesRead = ::read(this->fd, buffer, size);

    if (bytesRead < 0) {
        return -1;
    }

    string str(buffer, bytesRead);

    // Locate the last `\n`
    size_t lastPos = str.find_last_of("\n");
    if (lastPos == string::npos) {
        return -1; // No newline found
    }

    // Locate the penultimate `\n`
    size_t penultimatePos = str.find_last_of("\n", lastPos - 1);

    if (penultimatePos == string::npos) {
        // Only one line in the file
        *data = str.substr(0, lastPos);
    } else {
        // Extract the last line
        *data = str.substr(penultimatePos + 1, lastPos - penultimatePos - 1);
    }

    return 0;
}

/**
 * @brief Reads data from the file defined in the constructor.
 * @param data string pointer to store data read from the file
 * @return int 0 if success, -1 if error
 */
int Fs::read(string* data) {
    if (!isOpen()) {
        return -1;
    }

    int size = getSize();

    if (size <= 0) {
        return -1;
    }

    char buffer[size];

    // Set file pointer to the beginning of the file
    lseek(this->fd, 0, SEEK_SET);

    ssize_t bytesRead = ::read(this->fd, buffer, size);

    if (bytesRead < 0) {
        return -1;
    }

    *data = string(buffer, bytesRead);

    return 0;
}

/**
 * @brief Writes data to the file defined in the constructor on a new line.
 * @param data string pointer to data to be written to the file
 * @return int 0 if success, -1 if error
 */
int Fs::writeOnNewLine(string* data) {
    if (!isOpen()) {
        return -1; 
    }

    // Move the cursor to the end of the file
    if (lseek(this->fd, 0, SEEK_END) < 0) {
        return -1;
    }

    std::string dataWithNewline = *data;
    if (dataWithNewline.back() != '\n') {
        dataWithNewline += '\n'; // Add newline if not already present
    }

    if (::write(this->fd, dataWithNewline.c_str(), dataWithNewline.size()) < 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief Renames the file to a new path.
 * @param newpath string pointer to the new path
 * @return int 0 if success, -1 if error
 */
int Fs::rename(string* newpath) {
    if (isOpen()) {
        throw runtime_error("Cannot move an open file. Close the file first.");
    }

    std::string newpath_str = *newpath;
    if (::rename(this->path.c_str(), newpath_str.c_str()) != 0) {
        return -1;
    }

    this->path = newpath_str;

    return 0;
}
