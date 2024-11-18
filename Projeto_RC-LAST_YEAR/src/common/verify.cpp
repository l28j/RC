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

// string with 8 alphanumerics
bool Verify::isPassword(string password) {
    if(password.length() != 8) {
        return false;
    }

    for(char c: password) {
        if(!isAlphanumeric(c)) {
            return false;
        }
    }

    return true;
}

// string with up to 10 alphanumerics
bool Verify::isAuctionName(string name) {
    if(name.length() == 0 || name.length() > 10) {
        return false;
    }

    for(char c: name) {
        if(!isAlphanumeric(c)) {
            return false;
        }
    }

    return true;
}

// string with up to 6 digits
bool Verify::isAuctionStartValue(string startValue) {
    if(startValue.length() == 0 || startValue.length() > 6) {
        return false;
    }

    for(char c: startValue) {
        if(!isDigit(c)) {
            return false;
        }
    }

    return true;
}

// string with up to 5 digits
bool Verify::isAuctionDuration(string duration) {
    if(duration.length() == 0 || duration.length() > 5) {
        return false;
    }

    for(char c: duration) {
        if(!isDigit(c)) {
            return false;
        }
    }

    if (stoi(duration) <= 0){
      return false;
    }

    return true;
}

// string with up to 3 digits
bool Verify::isAID(string aid) {
    if(aid.length() == 0 || aid.length() > 3) {
        return false;
    }

    for(char c: aid) {
        if(!isDigit(c)) {
            return false;
        }
    }

    return true;
}

// string with up to 24 alphanumerics, dashes (-), underscores (_) and dots (.)
bool Verify::isFileName(string fileName) {
    size_t len = fileName.length();

    if(len == 0 || len > 24) {
        return false;
    }

    for(char c: fileName) {
        if(!isAlphanumeric(c) && c != '-' && c != '_' && c != '.') {
            return false;
        }
    }

    return true;
}