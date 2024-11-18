#ifndef USER_UNREGISTER_H
#define USER_UNREGISTER_H

#include "../command.hpp"

class Unregister : public Command {
    public:
        Unregister() : Command(UDP, UNREGISTER) {};

        int execute() override;

        void send() override;
        void receive() override;

        string formatData() override;
};

#endif // UNREGISTER_H
