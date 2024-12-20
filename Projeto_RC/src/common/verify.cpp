#include "verify.hpp"

// Checks if the character is a digit (0-9).
bool Verify::isDigit(char digit) {
    if (digit >= '0' && digit <= '9') {
        return true;
    }
    return false;
}

// Checks if the character is a letter (a-z or A-Z).
bool Verify::isLetter(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return true;
    }
    if (letter >= 'A' && letter <= 'Z') {
        return true;
    }
    return false;
}

// Checks if the character is alphanumeric (a letter or a digit).
bool Verify::isAlphanumeric(char c) {
   return isDigit(c) || isLetter(c);
}

// Checks if the string represents a valid number (contains only digits).
bool Verify::isNumber(string number) {
    for(char c: number) {
        if(!isDigit(c)) {
            return false;
        }
    }
    return true;
}

// Checks if the string is a valid UID (6 digits).
bool Verify::isUID(string uid) {
    if(uid.length() != 6) {
        return false;
    }
    for(char c: uid) {
        if(!isDigit(c)) {
            return false;
        }
    }
    return true;
}

// Checks if the string represents a valid color (one of R, G, B, Y, P, O).
bool Verify::isColor(string color) {
    if(color.length() != 1) {
        return false;
    }
    if (color[0] != 'R' && color[0] != 'G' && color[0] != 'B'
        && color[0] != 'Y' && color[0] != 'P' && color[0] != 'O') {
        return false;
    }
    return true;
}
