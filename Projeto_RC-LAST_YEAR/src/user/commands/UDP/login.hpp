#ifndef USER_LOGIN_H
#define USER_LOGIN_H

#include "../command.hpp"

class Login : public Command {
    private:
        string user;
        string password;

    public:
        Login(string user, string password) 
            : Command(UDP, LOGIN), user(user), password(password) {};

        int execute() override;
        
        void send() override;
        void receive() override;

        string formatData() override;
};

#endif
