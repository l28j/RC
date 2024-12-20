#include "fs.hpp"
#include <sys/stat.h>

// Returns the file path associated with this Fs instance.
string Fs::getPath() {
    return this->path;
}

/**
 * @brief Opens the file specified in the constructor.
 * @param mode READ or WRITE
 * @return int 0 if success, -1 if error
 */
int Fs::open(int mode) {
    if (mode == READ) {
        this->fd = ::open(this->path.c_str(), O_RDONLY, 0644); // Open file in read-only mode.
    } else if (mode == WRITE) {
        this->fd = ::open(this->path.c_str(), O_WRONLY | O_CREAT, 0644); // Open file in write mode, creating if necessary.
    } else {
        return -1; // Invalid mode.
    }

    return this->fd >= 0 ? 0 : -1; // Return success or failure.
}

/**
 * @brief Closes the file associated with this Fs instance.
 * @return int 0 if success, -1 if error
 */
int Fs::close() {
    if (!isOpen() || ::close(this->fd) < 0) {
        return -1; // Return error if the file is not open or closing fails.
    }

    this->fd = -1; // Reset the file descriptor.
    return 0;
}

/**
 * @brief Checks if the file is currently open.
 * @return true if the file is open, false otherwise.
 */
bool Fs::isOpen() {
    return this->fd != -1;
}

/**
 * @brief Writes data to the file.
 * @param data Pointer to the string containing the data to write.
 * @return int 0 if success, -1 if error
 */
int Fs::write(string* data) {
    if (!isOpen()) {
        return -1; // Return error if the file is not open.
    }

    return ::write(this->fd, data->c_str(), data->size()) >= 0 ? 0 : -1; // Write to the file and return the result.
}

/**
 * @brief Gets the size of the file in bytes.
 * @return int -1 if error, otherwise file size in bytes.
 */
int Fs::getSize() {
    if (!isOpen()) {
        return -1; // Return error if the file is not open.
    }

    lseek(this->fd, 0, SEEK_SET); // Move to the start of the file.
    size_t size = lseek(this->fd, 0, SEEK_END); // Get the file size.
    lseek(this->fd, 0, SEEK_SET); // Reset the file pointer to the start.

    return static_cast<int>(size); // Return the file size.
}

/**
 * @brief Reads the first line of the file.
 * @param data Pointer to the string where the first line will be stored.
 * @return int 0 if success, -1 if error
 */
int Fs::getFirstLine(string* data) {
    if (!isOpen()) {
        return -1; // Return error if the file is not open.
    }

    int size = getSize(); // Get the size of the file.

    if (size <= 0) {
        return -1; // Return error if the file size is invalid.
    }

    char buffer[size];
    lseek(this->fd, 0, SEEK_SET); // Move to the start of the file.
    ssize_t bytesRead = ::read(this->fd, buffer, size); // Read the file data.

    if (bytesRead < 0) {
        return -1; // Return error if reading fails.
    }

    string str(buffer, bytesRead);
    size_t pos = str.find("\n"); // Find the position of the newline character.

    if (pos == string::npos) {
        return -1; // Return error if no newline is found.
    }

    *data = str.substr(0, pos); // Extract the first line.
    return 0;
}



/**
 * @brief Reads all data from the file defined in the constructor.
 * @param data Pointer to the string where the file content will be stored.
 * @return int 0 if success, -1 if error.
 */
int Fs::read(string* data) {
    if (!isOpen()) {
        return -1; // Return error if the file is not open.
    }

    int size = getSize(); // Get the size of the file.

    if (size <= 0) {
        return -1; // Return error if the file size is invalid.
    }

    char buffer[size];
    lseek(this->fd, 0, SEEK_SET); // Move to the start of the file.
    ssize_t bytesRead = ::read(this->fd, buffer, size); // Read the file content.

    if (bytesRead < 0) {
        return -1; // Return error if reading fails.
    }

    *data = string(buffer, bytesRead); // Store the read data into the provided string.
    return 0;
}

/**
 * @brief Writes data to the file on a new line.
 * @param data Pointer to the string containing data to be written to the file.
 * @return int 0 if success, -1 if error.
 */
int Fs::writeOnNewLine(string* data) {
    if (!isOpen()) {
        return -1; // Return error if the file is not open.
    }

    if (lseek(this->fd, 0, SEEK_END) < 0) {
        return -1; // Return error if seeking to the end fails.
    }

    string dataWithNewline = *data;
    if (dataWithNewline.back() != '\n') {
        dataWithNewline += '\n'; // Add a newline if not already present.
    }

    return ::write(this->fd, dataWithNewline.c_str(), dataWithNewline.size()) >= 0 ? 0 : -1; // Write the data.
}

/**
 * @brief Renames the file to a new path.
 * @param newpath Pointer to the string containing the new file path.
 * @return int 0 if success, -1 if error.
 */
int Fs::rename(string* newpath) {
    if (isOpen()) {
        throw runtime_error("Cannot move an open file. Close the file first."); // Prevent renaming if the file is open.
    }

    string newpath_str = *newpath;
    if (::rename(this->path.c_str(), newpath_str.c_str()) != 0) {
        return -1; // Return error if renaming fails.
    }

    this->path = newpath_str; // Update the path to the new name.
    return 0;
}
