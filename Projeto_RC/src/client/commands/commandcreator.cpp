#include "commandcreator.hpp"


Command* CommandFactory::createCommand(string command, vector<string> arguments) {
    if (command == START) {
        return CommandFactory::createStart(arguments);
    } else if (command == TRY) {    
        return CommandFactory::createTry(arguments);
    } else if (command == SHOW_TRIALS || command == ST) {
        return CommandFactory::createShowTrials(arguments);
    } else if (command == SCORE_BOARD || command == SB) {
        return CommandFactory::createScoreboard(arguments);
    } else if (command == QUIT || command == EXIT) {
        return CommandFactory::createQuit(arguments);
    } else if (command == DEBUG) {
        return CommandFactory::createDebug(arguments);
    } else {
        printf("Invalid command\n");
        return nullptr;
    }
}

Command* CommandFactory::createStart(vector<string> arguments) {
    if (arguments.size() != 2) {
        printf("Invalid number of arguments\n");
        printf("Usage: start <ID> <game_time>\n");
        return nullptr;
    }

    string ID = arguments[0];
    string game_time = arguments[1];
    
    if(!Verify::isNumber(game_time)){
        printf("Invalid game time\n");
        return nullptr;
    }
    if(!Verify::isUID(ID)){
        printf("Invalid ID\n");
        return nullptr;
    }

    return new Start(ID, game_time);
}

Command* :: CommandFactory::createTry(vector<string> arguments) {
    if (arguments.size() != 4) {
        printf("Invalid number of arguments\n");
        printf("Usage: try <color1> <color2> <color3> <color4>\n");
        return nullptr;
    }

    string colors [4] = {arguments[0], arguments[1], arguments[2], arguments[3]};
    
    for (string color : colors) {
        if (!Verify::isColor(color)) {
            printf("Invalid color\n");
            return nullptr;
        }
    }

    return new Try(color);
}

Command* CommandFactory::createShowTrials(vector<string> arguments) {
    if (arguments.size() != 0) {
        printf("Invalid number of arguments\n");
        printf("Usage: show_trials\n");
        return nullptr;
    }

    return new ShowTrials();
}

Command* CommandFactory::createScoreboard(vector<string> arguments) {
    if (arguments.size() != 0) {
        printf("Invalid number of arguments\n");
        printf("Usage: scoreboard\n");
        return nullptr;
    }

    return new Scoreboard();
}

Command* CommandFactory::createQuit(vector<string> arguments) {
    if (arguments.size() != 0) {
        printf("Invalid number of arguments\n");
        printf("Usage: quit\n");
        return nullptr;
    }

    return new Quit();
}

Command* CommandFactory::createExit(vector<string> arguments) {
    if (arguments.size() != 0) {
        printf("Invalid number of arguments\n");
        printf("Usage: exit\n");
        return nullptr;
    }

    return new Exit();
}

Command* CommandFactory::createDebug(vector<string> arguments) {
    if (arguments.size() != 6) {
        printf("Invalid number of arguments\n");
        printf("Usage: debug <ID> <game_time> <color1> <color2> <color3> <color4>\n");
        return nullptr;
    }

    return new Debug();
}