#ifndef USER_CONSTANTS_H
#define USER_CONSTANTS_H

#define UDP 1
#define TCP 2

#define IP_FLAG "-n"
#define PORT_FLAG "-p"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 58031

#define MAX_MESSAGE_SIZE 1024
#define MAX_TCP_REPLY_SIZE 1024

#define START "start"
#define TRY "try"
#define SHOW_TRIALS "show_trials"
#define ST "st"
#define SCORE_BOARD "scoreboard"
#define SB "sb"
#define QUIT "quit"
#define EXIT "exit"
#define DEBUG "debug"

#define GAME_START "Game started\n"
#define GAME_END "Exiting..... \nGame ended\n"
#define GAME_OVER "Game over\n"

#define OK "OK"
#define NOK "NOK"
#define ERR "ERR"

//UCP
#define SNG "SNG"
#define RSG "RSG"
#define TRY_ "TRY"
#define RTR "RTR"
#define DUP "DUP"   
#define INV "INV"
#define ENT "ENT"
#define ETM "ETM"
#define QUT "QUT"
#define RQT "RQT"
#define DBG "DBG"
#define RDB "RDB"
//TCP
#define STR "STR"
#define RST "RST"
#define SSB "SSB"
#define RSS "RSS"
#define SSB "SSB"
#define ACT "ACT"
#define FIN "FIN"


#define RED "R"
#define GREEN "G"
#define BLUE "B"
#define YELLOW "Y"
#define ORANGE "O"
#define PURPLE "P"

#define MAX_TRIALS 8
#define MAX_TIME 600 // max time in seconde

#define PLAYER_IS_PLAYING "You are already playing\n"
#define PLAYER_NOT_PLAYING "You are not playing\n"
#define ONGOING_GAME "There is already a game in progress with this ID\n"
#define WIN "You won\n"
#define DUPLICATE "You already tried this combination\n"
#define INVALID "Invalid \n"
#define INVALID_COMMAND_TRY "Invalid command\nUsage: try <color1> <color2> <color3> <color4>\n"
#define AVAILABLE_COLORS "Available colors: R(red), G(green), B(blue), Y(yellow), O(orange), P(purple)\n"
#define TIME_IS_OVER "You have reached the maximum time\n"
#define INVALID_COMMAND_DEBUG "Invalid command\nUsage: debug <ID> <game_time> <color1> <color2> <color3> <color4>\n"
#define NO_GAMES "There are no games to show\n"

#endif
