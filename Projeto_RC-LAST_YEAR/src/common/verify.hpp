#ifndef COMMON_VERIFY_H
#define COMMON_VERIFY_H

#include <string>

using namespace std;

class Verify {
    public:
        static bool isUID(string uid);
        static bool isPassword(string password);

        static bool isAuctionName(string name);
        static bool isAuctionStartValue(string startValue);
        static bool isAuctionDuration(string duration);

        static bool isAID(string aid);

        static bool isFileName(string fileName);

        static bool isNumber(string number);
        static bool isDigit(char digit);
        static bool isLetter(char letter);
        static bool isAlphanumeric(char c);
    
};

#endif