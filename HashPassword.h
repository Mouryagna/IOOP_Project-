#ifndef HASHPASSWORD_H
#define HASHPASSWORD_H

#include <string>
using namespace std;

class Protection {
public:
    char* generateSalt(int length);
    char* HashPass(const char* password, const char* salt);
};

#endif
