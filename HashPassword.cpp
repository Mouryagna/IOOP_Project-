#include<cstring>
#include<iostream>
#include"HashPassword.h"
#include<random>

const char* Protection::generateSalt(int length){
    static char salt[50];
    std::string chars ="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    srand(time(0));
    for(int i=0;i<length;i++){
        salt[i]=chars[rand()%chars.size()];
    }
    return salt;
}

const char* Protection::HashPass(const char*pass,const char* salt){
    static char hashed[50];
    unsigned long hashValue=0;
    
    char combined[100];
    strcpy(combined,pass);
    strcat(combined,salt);

    for(int i=0;combined[i]!='\0';i++){
        int ascii=(int)combined[i];
        hashValue=(hashValue*31)+ascii;
    }

    itoa(hashValue,hashed,10);
    return hashed;
};