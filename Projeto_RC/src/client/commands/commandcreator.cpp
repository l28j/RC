#include "commandcreator.hpp"
#include "../constants.hpp"
#include "UDP/Start.hpp"
#include "UDP/Try.hpp"
#include "TCP/Show_Trials.hpp"
#include "TCP/Scoreboard.hpp"
#include "UDP/Quit.hpp"
#include "UDP/Debug.hpp"
#include "UDP/Exit.hpp"

// Factory method to create the appropriate command object based on input.
Command* CommandFactory::createCommand(string command, vector<string> arguments) {
    if (command == START) {
        return CommandFactory::createStart(arguments);
    } else if (command == TRY) {    
        return CommandFactory::createTry(arguments);
    } else if (command == SHOW_TRIALS || command == ST) {
        return CommandFactory::createShowTrials(arguments);
    } else if (command == SCORE_BOARD || command == SB) {
        return CommandFactory::createScoreboard(arguments);
    } else if (command == QUIT) {
        return CommandFactory::createQuit(arguments);
    } else if (command == DEBUG) {
        return CommandFactory::createDebug(arguments);
    } else if (command == EXIT) {
        return CommandFactory::createExit(arguments);
    } else {
        printf("Invalid command\n");
        return nullptr;
    }
}

// Creates a Start command after validating its arguments.
Command* CommandFactory::createStart(vector<string> arguments) {
    if (arguments.size() != 2) {
        printf("Invalid number of arguments\n");
        printf("Usage: start <ID> <game_time>\n");
        return nullptr;
    }
    if (!Verify::isUID(arguments[0])) {
        printf("Invalid ID\n");
        return nullptr;
    }
    if (!Verify::isNumber(arguments[1]) || stoi(arguments[1]) < 1 || stoi(arguments[1]) > 600) {
        printf("Invalid game time\n");
        return nullptr;
    }
   
    return new Start(arguments[0], arguments[1]);
}

// Creates a Try command after validating its arguments.
Command* CommandFactory::createTry(vector<string> arguments) {
    if (arguments.size() != 4) {
        printf("Invalid number of arguments\n");
        printf("Usage: try <color1> <color2> <color3> <color4>\n");
        return nullptr;
    }

    for (const string& color : arguments) {
        if (!Verify::isColor(color)) {
            printf("Invalid color\n");
            return nullptr;
        }
    }

    return new Try(arguments);
}

// Creates a Show_Trials command after validating its arguments.
Command* CommandFactory::createShowTrials(vector<string> arguments) {
    if (!arguments.empty()) {
        printf("Invalid number of arguments\n");
        printf("Usage: show_trials\n");
        return nullptr;
    }

    return new Show_Trials();
}

// Creates a Scoreboard command after validating its arguments.
Command* CommandFactory::createScoreboard(vector<string> arguments) {
    if (!arguments.empty()) {
        printf("Invalid number of arguments\n");
        printf("Usage: scoreboard\n");
        return nullptr;
    }

    return new Scoreboard();
}

// Creates a Quit command after validating its arguments.
Command* CommandFactory::createQuit(vector<string> arguments) {
    if (!arguments.empty()) {
        printf("Invalid number of arguments\n");
        printf("Usage: quit\n");
        return nullptr;
    }

    return new Quit();
}

// Creates an Exit command after validating its arguments.
Command* CommandFactory::createExit(vector<string> arguments) {
    if (!arguments.empty()) {
        printf("Invalid number of arguments\n");
        printf("Usage: exit\n");
        return nullptr;
    }

    return new Exit();
}

// Creates a Debug command after validating its arguments.
Command* CommandFactory::createDebug(vector<string> arguments) {
    if (arguments.size() != 6) {
        printf("Invalid number of arguments\n");
        printf("Usage: debug <ID> <game_time> <color1> <color2> <color3> <color4>\n");
        return nullptr;
    }
    if (!Verify::isUID(arguments[0])) {
        printf("Invalid ID\n");
        return nullptr;
    }

    if (!Verify::isNumber(arguments[1]) || stoi(arguments[1]) < 1 || stoi(arguments[1]) > 600) {
        printf("Invalid game time\n");
        return nullptr;
    }

    for (int i = 2; i < 6; i++) {
        if (!Verify::isColor(arguments[i])) {
            printf("Invalid color\n");
            return nullptr;
        }
    }

    return new Debug(arguments[0], arguments[1], arguments[2] + " " + arguments[3] + " " + arguments[4] + " " + arguments[5]);
}
