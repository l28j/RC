#include "verify.hpp"

bool Verify::isDigit(char digit) {
    if (digit >= '0' && digit <= '9') {
        return true;
    }

    return false;
}

bool Verify::isLetter(char letter) {
    if (letter >= 'a' && letter <= 'z') {
        return true;
    }

    if (letter >= 'A' && letter <= 'Z') {
        return true;
    }

    return false;
}

bool Verify::isAlphanumeric(char c) {
   return isDigit(c) || isLetter(c);
}

bool Verify::isNumber(string number) {
    for(char c: number) {
        if(!isDigit(c)) {
            return false;
        }
    }

    return true;
}

// string with 6 digits
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