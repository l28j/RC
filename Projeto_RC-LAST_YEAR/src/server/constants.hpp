#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define PORT_FLAG "-p"
#define VERBOSE_FLAG "-v"

#define DEFAULT_PORT 58098
#define DEFAULT_VERBOSE false

#define MAX_AUCTIONS 999
#define AUCTION_SIZE 5 // AID status
#define COMMAND_REPLY 3
#define STATUS 3

//receive protocol messages
#define LOGIN "LIN"
#define LOGOUT "LOU"
#define UNREGISTER "UNR"
#define MY_AUCTIONS "LMA"
#define MY_BIDS "LMB"
#define LIST_AUCTIONS "LST"
#define SHOW_RECORD "SRC"
#define OPEN_AUCTION "OPA"
#define CLOSE_AUCTION "CLS"
#define SHOW_ASSET "SAS"
#define PLACE_BID "BID"

//response protocol messages
#define RES_LOGIN "RLI"
#define RES_LOGOUT "RLO"
#define RES_UNREGISTER "RUR"
#define RES_MY_AUCTIONS "RMA"
#define RES_MY_BIDS "RMB"
#define RES_LIST_AUCTIONS "RLS"
#define RES_SHOW_RECORD "RRC"
#define RES_OPEN_AUCTION "ROA"
#define RES_CLOSE_AUCTION "RCL"
#define RES_SHOW_ASSET "RSA"
#define RES_PLACE_BID "RBD"

#define STATUS_OK "OK"   // Operation successful
#define STATUS_NOK "NOK" // Operation unsuccessful
#define STATUS_REG "REG" // User registered
#define STATUS_NLG "NLG" // Not logged in
#define STATUS_UNR "UNR" // User not registered
#define STATUS_ERR "ERR" // Error
#define STATUS_ACC "ACC" // Bid accepted
#define STATUS_REF "REF" // Bid refused
#define STATUS_ILG "ILG" // Invalid bid
#define STATUS_EAU "EAU" // Auction does not exist
#define STATUS_EOW "EOW" // Auction not owned by the user
#define STATUS_END "END" // Auction ended

//max protocol command size
#define CHUNCKS COMMAND_REPLY + 1 + STATUS + AUCTION_SIZE*MAX_AUCTIONS + 1
#define MAX_FILE_SIZE 10 * 1024 * 1024                            // 10MB = 10*1024*1024 Bytes
#define MAX_TCP_REPLY_SIZE 7 + 24 + 1 + 8 + 1 + MAX_FILE_SIZE + 1 // RSA <status(3)> <filename(24)> <filesize(8)> <filedata>

#endif