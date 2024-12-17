#include "fs.hpp"

#include <sys/stat.h>

string Fs::getPath() {
    return this->path;
}

/**
 * @brief opens file defined in constructor
 * @param mode READ or WRITE
 * @return int 0 if success, -1 if error
 */
int Fs::open(int mode) {
    // Isto nao consegue abrir o ficheiro dentro de uma pasta
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
 * @brief Closes file defined in constructor
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
 * @brief Checks if file defined in constructor is open
 * @return true if file is open
 * @return false if file is not open
 */
bool Fs::isOpen() {
    return this->fd != -1;
}

/**
 * @brief Writes data to file defined in constructor
 * @param data string pointer to data to be written to file
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
 * @brief returns size of file in bytes
 * 
 * @return int -1 if error, else file size in bytes
 */
int Fs::getSize() {
    if(!isOpen()) {
        return -1;
    }

    // set file pointer to beginning of file
    lseek(this->fd, 0, SEEK_SET);

    size_t size = lseek(this->fd, 0, SEEK_END);

    // set file pointer to beginning of file
    lseek(this->fd, 0, SEEK_SET);

    return static_cast<int>(size);
}

/**
 * @brief Reads first line of file defined in constructor
 * @param data string pointer to store first line of file
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

    // set file pointer to beginning of file
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

    *data = str.substr(0, pos);

    return 0;
}



/**
 * @brief Reads data from file defined in constructor
 * @param data string pointer to store data read from file
 * @return int 0 if success, -1 if error
 */
int Fs::read(string* data) {
    if(!isOpen()) {
        return -1;
    }

    int size = getSize();

    if(size <= 0) {
        return -1;
    }

    char buffer[size];

    // set file pointer to beginning of file
    lseek(this->fd, 0, SEEK_SET);

    ssize_t bytesRead = ::read(this->fd, buffer, size);

    if(bytesRead < 0) {
        return -1;
    }

    *data = string(buffer, bytesRead);

    return 0;
}

/**
 * @brief Writes data to file defined in constructor on a new line
 * @param data string pointer to data to be written to file
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

    std::string dataWithNewline = data->c_str();
    if (dataWithNewline.back() != '\n') {
        dataWithNewline += '\n'; // Add newline if not already present
    }

    if (::write(this->fd, dataWithNewline.c_str(), dataWithNewline.size()) < 0) {
        return -1;
    }

    return 0;
}

int Fs::rename(string* newpath) {

    if (isOpen()) {
        throw runtime_error("Cannot move an open file. Close the file first.");
    }

    std::string newpath_str = newpath->c_str();
    if (::rename(this->path.c_str(), newpath_str.c_str()) != 0) {
        return -1;
    }

    this->path = newpath_str;

    return 0;
}

