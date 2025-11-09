#include<iostream>
#include<fstream>
#include<string>
#include"accounts.h"
#include"HashPassword.h"
using namespace std;

void Account::createAccount(){
    cout<<"Enter Account Id:";
    cin>>Account::accId;
    cout<<"Enter Account holder name:";
    cin.getline(name,50);
    cout<<"Enter Initial Balence:";
    cin>>Account::accBalence;

    cout<<"Set Password:";
    string pwd;
    cin>>pwd;
    strcpy()



}
