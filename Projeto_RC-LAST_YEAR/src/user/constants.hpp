#ifndef USER_CONSTANTS_H
#define USER_CONSTANTS_H

#define UDP 1
#define TCP 2

#define IP_FLAG "-n"
#define PORT_FLAG "-p"
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 58098

#define UDP_VERBOSE false
#define TCP_VERBOSE false

#define CONNECTION_TIMEOUT 5

#define MAX_AUCTIONS 999
#define AUCTION_SIZE 5 // AID status
#define COMMAND_REPLY 3
#define STATUS 3
#define CHUNCKS COMMAND_REPLY + 1 + STATUS + AUCTION_SIZE*MAX_AUCTIONS + 1


#define MAX_FILE_SIZE 10*1024*1024 // 10MB = 10*1024*1024 Bytes
#define MAX_TCP_REPLY_SIZE 7+24+1+8+1+MAX_FILE_SIZE+1 // RSA <status(3)> <filename(24)> <filesize(8)> <filedata>

#define LOGIN "login"
#define LOGOUT "logout"
#define UNREGISTER "unregister"
#define EXIT "exit"
#define OPEN "open"
#define CLOSE "close"
#define MY_AUCTIONS "myauctions"
#define MY_AUCTIONS_SHORT "ma"
#define MY_BIDS "mybids"
#define MY_BIDS_SHORT "mb"
#define LIST "list"
#define LIST_SHORT "l"
#define SHOW_ASSET "show_asset"
#define SHOW_ASSET_SHORT "sa"
#define BID "bid"
#define BID_SHORT "b"
#define SHOW_RECORD "show_record"
#define SHOW_RECORD_SHORT "sr"

#define STATUS_OK "OK"
#define STATUS_NOK "NOK"
#define STATUS_REGISTERD "REG"
#define STATUS_UNREGISTERD "UNR"
#define STATUS_NOT_LOGGED_IN "NLG"
#define STATUS_NOT_FOUND "EAU"
#define STATUS_NOT_OWNED "EOW"
#define STATUS_ALREADY_CLOSED "END"
#define STATUS_ACCEPTED "ACC"
#define STATUS_REFUSED "REF"
#define STATUS_ILLEGAL "ILG"

#define UDP_LOGIN_COMMAND "LIN"
#define UDP_LOGOUT_COMMAND "LOU"
#define UDP_UNREGISTER_COMMAND "UNR"
#define UDP_MY_AUCTIONS_COMMAND "LMA"
#define UDP_MY_BIDS_COMMAND "LMB"
#define UDP_LIST_COMMAND "LST"
#define UDP_SHOW_RECORD_COMMAND "SRC"

#define UDP_LOGIN_RESPONSE "RLI"
#define UDP_LOGOUT_RESPONSE "RLO"
#define UDP_UNREGISTER_RESPONSE "RUR"
#define UDP_MY_AUCTIONS_RESPONSE "RMA"
#define UDP_MY_BIDS_RESPONSE "RMB"
#define UDP_LIST_RESPONSE "RLS"
#define UDP_SHOW_RECORD_RESPONSE "RRC"

#define TCP_SHOW_ASSET_COMMAND "SAS"
#define TCP_OPEN_COMMAND "OPA"
#define TCP_CLOSE_COMMAND "CLS" 
#define TCP_BID_COMMAND "BID"

#define TCP_SHOW_ASSET_RESPONSE "RSA"
#define TCP_OPEN_RESPONSE "ROA"
#define TCP_CLOSE_RESPONSE "RCL"
#define TCP_BID_RESPONSE "RBD"

#define NOT_LOGGED_IN "user not logged in"
#define USER_ALREADY_LOGGED_IN "user already logged in, please logout first"

#define LOGIN_SUCCESS "successfull login"
#define LOGIN_FAILURE "incorrect login attempt"
#define LOGIN_REGISTER "new user registered"

#define LOGOUT_SUCCESS "successfull logout"
#define LOGOUT_FAILURE "user not logged in"
#define LOGOUT_UNREGISTER "unknown user"

#define UNREGISTER_SUCCESS "successfull unregister"
#define UNREGISTER_FAILURE "incorrect unregister attempt"
#define UNREGISTER_UNREGISTER "unknown user"

#define MY_AUCTIONS_EMPTY "no ongoing auctions"
#define MY_AUCTIONS_FAILURE "user not logged in"

#define LIST_FAILURE "no auction was yet started"

#define MY_BIDS_EMPTY "no ongoing bids"
#define MY_BIDS_FAILURE "user not logged in"

#define SHOW_ASSET_FAILURE "asset not found"
#define SHOW_ASSET_SUCCESS "asset was saved successfully"

#define OPEN_FAILURE "auction not started"

#define CLOSE_SUCCESS "auction closed successfully"
#define CLOSE_FAILURE "user or password incorrect"
#define CLOSE_NOT_LOGGED_IN "user not logged in"
#define CLOSE_AUCTION_NOT_FOUND "auction not found"
#define CLOSE_AUCTION_NOT_OWNED "auction not owned by user"
#define CLOSE_ALREADY_CLOSED "auction already closed"

#define BID_NOT_ACTIVE "auction not active"
#define BID_NOT_LOGGED_IN "user not logged in"
#define BID_ACCEPTED "bid accepted"
#define BID_REFUSED "bid refused, value too low"
#define BID_ILLEGAL "illegal bid, cant bid on own auction"


#define INVALID_UID "invalid uid"
#define INVALID_PASSWORD "invalid password"
#define INVALID_AUCTION_NAME "invalid auction name"
#define INVALID_AUCTION_START_VALUE "invalid auction start value"
#define INVALID_AUCTION_DURATION "invalid auction time duration"
#define INVALID_AUCTION_FILE_NAME "invalid auction file name"
#define INVALID_AUCTION_FILE_SIZE "invalid auction file size"
#define INVALID_AID "invalid aid"
#define INVALID_VALUE "invalid value"


#endif // USER_CONSTANTS_H