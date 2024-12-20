#ifndef COMMON_VERIFY_H
#define COMMON_VERIFY_H

#include <string>

using namespace std;

class Verify {
    public:
        // Checks if a string is a valid UID (6 digits).
        static bool isUID(string uid);

        // Checks if a string represents a valid number (only digits).
        static bool isNumber(string number);

        // Checks if a character is a digit (0-9).
        static bool isDigit(char digit);

        // Checks if a character is a letter (a-z or A-Z).
        static bool isLetter(char letter);

        // Checks if a character is alphanumeric (letter or digit).
        static bool isAlphanumeric(char c);

        // Checks if a string represents a valid color (R, G, B, Y, P, O).
        static bool isColor(string color);
};

#endif
