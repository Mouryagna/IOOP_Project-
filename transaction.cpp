#include"transaction.h"
#include"accounts.h"
#include"Search.h"
#include<fstream>
#include<cstring>
#include<iostream>

using namespace std;

Transaction::Transaction(){
    transactionID=0;
    accountID=0;
    amount=0.0;
    balence=0.0;
    strcpy(type,"");
    strcpy(date,"");

}

void Transaction::recordTransaction(long long int accID,double amt,char *ttyp,char *tdate){
    Search s;
    if(!s.SearchById(accID)){
        cout << "Account not found for ID: " << accID << endl;
        return;
    }

    static int nextID=1000;
    transactionID=nextID++;
    accountID=accID;

    amount=amt;
    strcpy(type,ttyp);
    strcpy(date,tdate);

    ofstream out("transactions.dat", ios::binary | ios::app);
    if(!out){
        cout<<"No Files Found";
        return;
    }

    out.write(reinterpret_cast<char*>(this), sizeof(*this));
    out.close();

    cout<<"Transaction recorded: "<<type<<" of ₹"<<amount<<" for account "<<accID<<endl;
}

void Transaction::displayTransaction(){
    cout << "\nTransaction ID: " << transactionID
         << "\nDate: " << date
         << "\nType: " << type
         << "\nAccount ID: " << accountID
         << "\nAmount: ₹" << amount << endl;
}

Account acc;

void Transaction::deposite(int accId, double amt) {
    if (amt <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }

    Search s;
    if (s.SearchById(accId)==false) {
        std::cout << "Account not found for ID: " << accId << std::endl;
        return;
    }

    char sign[] = "+";
    acc.change_balence(accId, sign, amt);

    char ttype[] = "Deposit";
    char tdate[20];
    time_t t = time(nullptr);
    strftime(tdate, sizeof tdate, "%Y-%m-%d %H:%M:%S", localtime(&t));
    recordTransaction(accId, amt, ttype, tdate);

    std::cout << "Deposited: ₹" << amt << " to account " << accId << std::endl;
}

void Transaction::withdraw(int accId, double amt) {
    if (amt <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }

    Search s;
    if (!s.SearchById(accId)) {
        std::cout << "Account not found for ID: " << accId << std::endl;
        return;
    }

    char sign[] = "-";
    acc.change_balence(accId, sign, amt);

    char ttype[] = "Withdrawal";
    char tdate[20];
    time_t t = time(nullptr);
    strftime(tdate, sizeof tdate, "%Y-%m-%d %H:%M:%S", localtime(&t));
    recordTransaction(accId, amt, ttype, tdate);

    std::cout << "Withdrew: ₹" << amt << " from account " << accId << std::endl;
}


