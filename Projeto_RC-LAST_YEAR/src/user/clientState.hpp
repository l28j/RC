#ifndef USER_CLIENTSTATE_H
#define USER_CLIENTSTATE_H

#include <string>

using namespace std;

/*
Class that holds the state of the client, like the current user and password
*/
class ClientState {
    public:
        void loginUser(string user, string password);
        void logoutUser();

        string getUser();
        void setUser(string user);

        string getPassword();
        void setPassword(string password);

        bool isLoggedIn();
    private:
        string user;
        string password;
};

#endif