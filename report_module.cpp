#include"report_module.h"
#include"accounts.h"
#include<iostream>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include <filesystem>
using namespace std;
report::report() {
    cout << "\n[Report Module Initialized Successfully]" << endl;

    if (!std::filesystem::exists("accounts.dat")) {
        cout << "Warning: accounts.dat not found. Reports may be incomplete.\n";
    }
}

void report::displayAllAccounts(){
    ifstream fin("accounts.dat",ios::binary);

    if(!fin){
        cout<<"No account data found.\n";
        return;
    }

    Account acc;

    cout<<"  All Accounts   ";

    while(fin.read(reinterpret_cast<char *>(&acc),sizeof(acc))){
        acc.displayAccount();

    }

    fin.close();
    

}

void report::showTotalBalence(){
    ifstream fin("accounts.dat",ios::binary);

    if(!fin){
        cout<<"No accounts found";
        return;
    }

    Account acc;
    double total=0;
    while(fin.read(reinterpret_cast<char *>(&acc),sizeof(acc))){
        total+=acc.getBalance();
    }

    cout<<"Total Balence of the Bank is:"<<total<<endl;
    fin.close();
}


