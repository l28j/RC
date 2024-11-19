#ifndef CLIENT_H
#define CLIENT_H

#include <string>

using namespace std;

/*
Class that holds the client
*/
class Client{
    public:
        bool isPlaying();

        string getID();
        void setID(string ID);

        string getGameTime();
        void setGameTime(string game_time);

    private:
        string ID;
        string game_time;
};

#endif