
#include "../constants.hpp"

#include "command.hpp"



#include <string>
#include <vector>

class CommandFactory {
public:
    static Command* createCommand(string command, vector<string> args);

private:
    
    static Command* createStart(vector<string> args);
    static Command* createTry(vector<string> args);
    static Command* createShowTrials(vector<string> args);
    static Command* createScoreboard(vector<string> args);
    static Command* createQuit(vector<string> args);
    static Command* createDebug(vector<string> args);
    
};