#ifndef __DATABASE_HPP__
#define __DATABASE_HPP__

#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

int userIsRegistered(string uid);
int userIsLoggedIn(string uid);

void logoutUser(string uid);
void registerUser(string uid, string password);
void unregisterUser(string uid);

int passwordMatches(string uid, string password);
void createLoginFile(string uid);

string createAuction(string uid, string name, string startValue, string timeActive, string fName, string fData);
bool closeAuction(string aid);

int auctionExists(string aid);
int isOwnerAuction(string uid, string aid);
int auctionIsFinished(string aid);

string getUserAuctions(string uid);

string getAllAuctions();

int getAuctionState(string aid);
string getAuctionAsset(string aid);
string getAuctionInfo(string aid);
string getAuctionBidsInfo(string aid);
string getAuctionEndInfo(string aid);
int getAuctionTimeActive(string aid);

string getUserBids(string uid);
bool isHigherBid(string aid, string value);
void placeBid(string uid, string aid, string value);

#endif  