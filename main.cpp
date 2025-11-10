#include<iostream>
#include<ctime>
#include<iomanip>
#include "accounts.h"
#include "transaction.h"
#include "search.h"
#include "report_module.h"
#include "HashPassword.h"
using namespace std;

void printMenu() {
    cout<<"\n=============== BANK MANAGEMENT SYSTEM ===============\n";
    cout<<"1. Create Account"<<endl;
    cout<<"2. Login Account"<<endl;
    cout<<"3. Edit Account"<<endl;
    cout<<"4. Delete Account"<<endl;
    cout<<"5. Deposit Amount"<<endl;
    cout<<"6. Withdraw Amount"<<endl;
    cout<<"7. Display All Accounts"<<endl;
    cout<<"8. Reports"<<endl;
    cout<<"9. Search Account"<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"Enter your Choice: ";
    cout<<"\n============================================================\n";
}
void reportMenu(report &r) {
    cout<<"\n=============== REPORT MODULE ===============\n";
    cout<<"1. Display All Accounts"<<endl;
    cout<<"2. Show Total Balance"<<endl;
    cout<<"0. back to Main Menu"<<endl;
    cout<<"\n============================================================\n";

    int ch;
    cout<<"Enter Choice: ";
    cin>>ch;
    switch(ch) {
        case 1: r.displayAllAccounts();break;
        case 2: r.showTotalBalence();break;
        case 0: cout<<"Returning to Main Menu..."<<endl;break;
        default: cout<<"Invalid Choice."<<endl;break;
    }
}
void searchMenu() {
    Search s;
    int ch;
    cout<<"\n=============== SEARCH MODULE ===============\n";
    cout<<"1. Search by Account ID"<<endl;
    cout<<"2. Search by Name"<<endl;
    cout<<"0. back to Main Menu"<<endl;
    cout<<"\n============================================================\n";
    cout<<"Enter Choice: ";
    cin>>ch;

    if(ch==1) {
        int id;
        cout<<"Enter Account ID: ";
        cin>> id;
        s.SearchById(id);
    } else if(ch==2) {
        string name;
        cout<<"Enter Account Name: ";
        cin>> name;
        s.SearchByName(name);
    } else if(ch==0) {
        cout<<"Returning to Main Menu..."<<endl;
    } else {
        cout<<"Invalid choice."<<endl;
    }
}

void hashDemo() {
    cout<<"\n=============== PASSWORD HASHING DEMO ===============\n";
    string pass;
    cout<<"Enter a password to hash: ";
    cin>> pass;

    const char* salt=Protection::generateSalt(8);
    const char* hashed=Protection::HashPass(pass.c_str(),salt);
    cout<<"Generated Salt: "<<salt<<endl;
    cout<<"Hashed Password: "<<hashed<<endl;
    cout<<"\n============================================================\n";
}
int main() {
    Account acc;
    Transaction txn;
    report rep;
    int choice;
    do {
        printMenu();
        cin>>choice;

        switch(choice) {
            case 1: acc.createAccount();break;
            case 2: acc.loginAccount();break;
            case 3: acc.editAccount();break;
            case 4: acc.deleteAccount();break;
            case 5: {
                int id;
                double amt;
                cout<<"Enter Account ID: ";
                cin>>id;
                cout<<"Enter Amount to Deposit";
                cin>>amt;

                time_t now = time(0);
                char* dt=ctime(&now);
                txn.deposite(id,amt);
                txn.recordTransaction(id,amt,(char*)"Deposit",dt);
                break;
            }
            case 6: {
                int id;
                double amt;
                cout<<"Enter Account ID: ";
                cin>>id;
                cout<<"Enter Amount to Withdraw";
                cin>>amt;

                time_t now = time(0);
                char* dt=ctime(&now);
                Account a;
                a.change_balence(id,(char*)"-",amt);
                txn.recordTransaction(id,amt,(char*)"Withdraw",dt);
                break;
            }
            case 7: rep.displayAllAccounts();break;
            case 8: reportMenu(rep);break;
            case 9: searchMenu();break;
            case 10: hashDemo(); break;
            case 0:
                cout<<"\nThank you for using the Bank Management System!"<<endl;break;
            default:
                cout<<"Invalid choice. Please try again.\n";
                break;
        }
    } while(choice!=0);
    return 0;
}