#ifndef CLIENT_ERRORS_H
#define CLIENT_ERRORS_H

#include <string>

#include <exception>

#include "constants.hpp"

#define UNKNOW_ERROR_MSG "Unknow error"

#define CONNECTION_TIMEOUT_MSG "Connection timed out"
#define CONNECTION_SETUP_MSG "Failed to establish connection"
#define CONNECTION_FAILED "Connection failed"

#define FILE_SIZE_ERROR "File size is too big"

#define SERVER_DATA_FORMAT "Server data format is invalid"

#define FS_READ_ERROR "Failed to read file"
#define FS_WRITE_ERROR "Failed to write file"

using namespace std;

class CostumError : public exception {
    public:
        CostumError(string msg): msg(msg) {}

        const char* what() const throw() {
            return msg.c_str();
        }

    protected:
        string msg;
};

class ConnectionSetupError : public CostumError {
    public:
        ConnectionSetupError(): CostumError(CONNECTION_SETUP_MSG) {}
};

class ConnectionFailedError : public CostumError {
    public:
        ConnectionFailedError(): CostumError(CONNECTION_FAILED) {}
};

class ConnectionTimeoutError : public CostumError {
    public:
        ConnectionTimeoutError(): CostumError(CONNECTION_TIMEOUT_MSG) {}
};

class FileSizeError : public CostumError {
    public:
        FileSizeError(): CostumError(FILE_SIZE_ERROR) {}
};

class ServerResponseError : public CostumError {
    public:
        ServerResponseError(): CostumError(SERVER_DATA_FORMAT) {}
};

class FsReadError : public CostumError {
    public:
        FsReadError(): CostumError(FS_READ_ERROR) {}
};

class FsWriteError : public CostumError {
    public:
        FsWriteError(): CostumError(FS_WRITE_ERROR) {}
};

#endif