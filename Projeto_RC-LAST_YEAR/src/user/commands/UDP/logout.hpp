#ifndef USER_LOGOUT_H
#define USER_LOGOUT_H

#include "../command.hpp"

class Logout : public Command {
    public:
        Logout() : Command(UDP, LOGIN) {};

        int execute() override;

        void send() override;
        void receive() override;

        string formatData() override;
};

#endif // LOGOUT_H
