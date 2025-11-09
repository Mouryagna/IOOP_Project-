#ifndef ACCOUNT_H
#define ACCOUNTS_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Account{

    int accId;
    char name[30];
    double accBalance;
    char passHash[30];
    
    public:
        Account();
        void createAccount();
        bool loginAccount();
        void displayAccount() const;
        void editAccount();
        void deleteAccount();
};

#endif