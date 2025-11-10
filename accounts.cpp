#include<iostream>
#include<fstream>
#include<cstring>
#include"accounts.h"
#include"HashPassword.h"
using namespace std;

Account::Account(): accId(0),accBalance(0.0) {
    strcpy(name,"");
    strcpy(passHash,"");
}


void Account::createAccount(){
    ofstream file("data/accounts.dat", ios::binary | ios::app);
    cout<<"Enter Account Id:";
    cin>>Account::accId;

    cout<<"Enter Account holder name:";
    cin>> name;

    cout<<"Set Password:";
    cin>> pass;

    const char*gensalt=Protection::generateSalt(length);
    strcpy(Account::salt, gensalt);
    const char* hashed = Protection::HashPass(pass, salt);
    strcpy(passHash,hashed);

    
    cout<<"Enter Initial Balence:";
    cin>>Account::accBalance;

    file.write((char*)this,sizeof(*this));
    file.close();
    cout<<"Account created successfully!"<<endl;
}
bool Account::loginAccount() {
    ifstream file("data/accounts.dat",ios::binary);
    if(!file) {
        cout<<"No accounts exist."<<endl;
        return false;
    }

    int inId;
    char inpass[30];
    char inpassHash[30];
    cout<<"Enter Account ID: ";
    cin>>inId;;
    cout<<"Enter Password: ";
    cin>>inpass;
    
    bool found=false;
    while(file.read((char*)this, sizeof(*this))) {
        if(accId == inId ) {
            const char* enteredHash = Protection::HashPass(inpass, salt);
            if(strcmp(passHash,inpassHash)==0){
                cout<<"Login successful. Welcome "<<name<<"!"<<endl;
                found=true;
            }else {
                cout << "\n❌ Wrong password.\n";
            }
            break;
        }
    }
    if(!found) {
        cout<<"Invalid Credentials."<<endl;
    }
    file.close();
    return found;
}
void Account::displayAccount() const {
    cout<<"Account ID: "<<accId<<endl;;
    cout<<"Account Holder: "<<name;
    cout<<"Balance: "<<accBalance;
}
int  Account :: getID(){
    return accId;
}
double Account :: getBalance(){
    return  accBalance;
}
const char* Account::getName() {
    return name;
}
void Account::editAccount() {
    fstream file("data/accounts.dat",ios::binary| ios::in| ios::out);
    if(!file) {
        cout<<"No accounts exist."<<endl;
        return;
    }
    int searchId;
    char inpass[30];
    cout<<"Enter Account ID to edit: ";
    cin>>searchId;
    cout<<"Enter Password: ";
    cin>>inpass;


    bool found=false;
    bool authorized= false;
    while(file.read((char*)this,sizeof(*this))) {
        if(accId==searchId) {
            found=true;
            if(strcmp(passHash,inpass)==0) {
                authorized=true;
                cout<<"\nAuthentication Successful."<<endl;
                cout<<"Current Details:"<<endl;
                displayAccount();

                cout<<endl;
                cout<<"Enter New Name: ";
                cin>>name;

                cout<<"Enter New Password";
                cin>> passHash;

                int pos=-1*sizeof(*this);
                file.seekp(pos,ios::cur);
                file.write((char*)this,sizeof(*this));
                cout << "\n Account details updated successfully!\n";
            }
            else {
                cout<<"Incorrect Password. Access denied."<<endl;
            }
            break;
        }
    }
    if (!found)
        cout << "Account not found.\n";

    file.close();
}
void Account::deleteAccount() {
    ifstream inFile("data/accounts.dat",ios::binary);
    ofstream outFile("data/temp.dat",ios::binary);
    if(!inFile || !outFile) {
        cout<<"Error opening file."<<endl;
        return;
    }
    int delId;
    char delpass[30];
    cout<<"Enter Account Id to Delete: ";
    cin>>delId;
    cout<<"Enter Password: ";
    cin>>delpass;

    bool found=false;
    bool deleted=false;

    while(inFile.read((char*)this,sizeof(*this))) {
        if(accId==delId) {
            found=true;
            if(strcmp(passHash,delpass)==0) {
                deleted=true;
                cout<<"Account "<<accId<<"( "<<name<<" ) deleted Successfully.\n";
                continue;
            }
            else {
                cout<<"incorrect password. Deletion aborted.\n";
                outFile.write((char*)this,sizeof(*this));
            }
        }
        else {
            outFile.write((char*)this,sizeof(*this));
        }
    }
    inFile.close();
    outFile.close();
    if(!deleted && !found) {
        remove("data/temp.dat");
        cout<<"Account not found.\n";
        return;
    }
    if (!deleted && found) {
        if (remove("data/accounts.dat") != 0) {
            cout << "Error removing original file.\n";
        } else {
            if (rename("data/temp.dat", "data/accounts.dat") != 0) {
                cout << "Error renaming temp file.\n";
            }
        }
        return;
    }
    if (remove("data/accounts.dat") != 0) {
        cout << "Error removing original file.\n";
    } else {
        if (rename("data/temp.dat", "data/accounts.dat") != 0) {
            cout << "Error renaming temp file.\n";
        }
    }
}