#ifndef COMMON_VERIFY_H
#define COMMON_VERIFY_H

#include <string>

using namespace std;

class Verify {
    public:
        static bool isUID(string uid);

        static bool isNumber(string number);
        static bool isDigit(char digit);
        static bool isLetter(char letter);
        static bool isAlphanumeric(char c);

        static bool isColor(string color);
    
};

#endif