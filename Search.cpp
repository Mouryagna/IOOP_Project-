#include"Search.h"
#include"accounts.h"
#include<cstring>
bool Search::SearchById(int id){
    ifstream file("data/accounts.dat",ios::binary);
    Account acc;
    bool found = false;
    while(file.read((char*)&acc,sizeof(acc))){
        if(acc.getID()==id){
                        cout<<"Account Found: "<<id<<" Balance: "<<acc.getBalance()<<endl;
                        found=true;
                        return found;
        }
    }
    file.close();
    cout<<" Account not found.\n";
    return found;
}

bool Search::SearchByName(string n) {
    ifstream file("data/accounts.dat", ios::binary);
    Account acc;
    bool found = false;

    while (file.read((char*)&acc, sizeof(acc))) {
        if (strcmp(acc.getName(), n.c_str()) == 0) {
            cout << "Account Found: " << acc.getID() << " Name: " << acc.getName() << " Balance: " << acc.getBalance() << endl;
            found = true;
            return found;
        }
    }
    
    file.close();
    cout << "Account not found.\n";
    return found;
}