#define ACCOUNTS_H

#include<iostream>
#include<string>
using namespace std;

class Account{

    int accId;
    char name[50];
    double accBalence;
    char passHash[50];
    
    public:
        void createAccount();
        void displayAccount() const;
        void editAccount();
        int getAccountID() const{return accId;}
};