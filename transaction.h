#if !defined(TRANSACTION_H)
#define TRANSACTION_H

#include<iostream>
#include<cstring>
using namespace std;

class Transaction{
    int transactionID;
    int accountID;
    double amount;
    double balence;
    char type[10];
    char date[20];
public:
    Transaction();

    void recordTransaction(int accID,double amt,char*ttyp,char*data);
    void displayTransaction();

    void deposite(int accId,double amount);
    void withdraw(int accid,double amount);

    int getAccId()const{return accountID;}
    double getAmount() const {return amount;}
    const char*getType()const {return type;}

    
};

#endif 
