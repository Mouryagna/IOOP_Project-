#ifndef ACCOUNT_H
#define ACCOUNTS_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Account{

    long long int accId;
    char name[30];
    double accBalance;
    int length=8;
    char pass[30];
    char salt[20];
    char passHash[30];
    
    public:
        Account();
        void createAccount();
        bool loginAccount();
        void displayAccount() const;
        void editAccount();
        long long int getID();
        const char* getName();
        double getBalance();
        void deleteAccount();
        void change_balence(int accid,char *sign,double amt);
        void deleteAllAccounts();

};

#endif