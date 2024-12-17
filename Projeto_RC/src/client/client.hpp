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

        string getTrials();
        void setTrials(string trials);

        bool isWin();
        void setWin(bool win);

        bool isLose();
        void setLose(bool lose);

        void reset();

    private:
        string ID;
        string game_time;
        string trials = "0";
        bool win = false;
        bool lose = false;
};

#endif