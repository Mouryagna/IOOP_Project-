#include <iostream>
#include <fstream>
#include <cstring>
#include "accounts.h"
#include "HashPassword.h"
using namespace std;


Account::Account() : accId(0), accBalance(0.0) {
    strcpy(name, "");
    strcpy(passHash, "");
    strcpy(salt, "");
}

void Account::createAccount() {
    ofstream file("accounts.dat", ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    cout << "Enter Account ID: ";
    cin >> accId;
    cout << "Enter Account Holder Name: ";
    cin >> name;

    char pass[30];
    cout << "Set Password: ";
    cin >> pass;

    Protection pt;
    const char* genSalt =pt.generateSalt(16);
    strcpy(salt, genSalt);

    const char* hashed = pt.HashPass(pass, salt);
    strcpy(passHash, hashed);

    cout << "Enter Initial Balance: ";
    cin >> accBalance;

    file.write(reinterpret_cast<char*>(this), sizeof(*this));
    file.close();
    cout << "Account created successfully!\n";
}

bool Account::loginAccount() {
    ifstream file("accounts.dat", ios::binary);
    if (!file) {
        cout << "No accounts exist.\n";
        return false;
    }

    int inId;
    char inputPass[30];
    cout << "Enter Account ID: ";
    cin >> inId;
    cout << "Enter Password: ";
    cin >> inputPass;

    bool found = false;
    while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (accId == inId) {
            Protection pt;
            const char* hashedInput = pt.HashPass(inputPass, salt);
            if (strcmp(passHash, hashedInput) == 0) {
                cout << "Login successful. Welcome " << name << "!\n";
                found = true;
            } else {
                cout << "Incorrect password.\n";
            }
            break;
        }
    }

    if (!found)
        cout << "Account not found.\n";

    file.close();
    return found;
}

void Account::displayAccount() const {
    cout << "\n--- Account Details ---\n";
    cout << "Account ID     : " << accId << endl;
    cout << "Account Holder : " << name << endl;
    cout << "Balance        : " << accBalance << endl;
    cout << "------------------------\n";
}

void Account::editAccount() {
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No accounts exist.\n";
        return;
    }

    int searchId;
    char inputPass[30];
    cout << "Enter Account ID to edit: ";
    cin >> searchId;
    cout << "Enter Password: ";
    cin >> inputPass;

    bool found = false, authorized = false;

    while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (accId == searchId) {
            found = true;

            Protection pt;
            const char* hashedInput = pt.HashPass(inputPass, salt);
            if (strcmp(passHash, hashedInput) == 0) {
                authorized = true;
                cout << "\nAuthentication Successful.\n";
                displayAccount();

                cout << "\nEnter New Name: ";
                cin >> name;

                char newPass[30];
                cout << "Enter New Password: ";
                cin >> newPass;

                Protection pt;
                char* newSalt = pt.generateSalt(16);
                strcpy(salt, newSalt);

                const char* newHash = pt.HashPass(newPass, salt);
                strcpy(passHash, newHash);

                int pos = -1 * static_cast<int>(sizeof(*this));
                file.seekp(pos, ios::cur);
                file.write(reinterpret_cast<char*>(this), sizeof(*this));
                cout << "Account details updated successfully!\n";
            } else {
                cout << "Incorrect Password. Access denied.\n";
            }
            break;
        }
    }

    if (!found)
        cout << "Account not found.\n";

    file.close();
}

void Account::deleteAccount() {
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    if (!inFile || !outFile) {
        cout << "Error opening file.\n";
        return;
    }

    int delId;
    char inputPass[30];
    cout << "Enter Account ID to delete: ";
    cin >> delId;
    cout << "Enter Password: ";
    cin >> inputPass;

    bool found = false, deleted = false;

    while (inFile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
        if (accId == delId) {
            found = true;
            Protection pt;
            const char* hashedInput = pt.HashPass(inputPass, salt);
            if (strcmp(passHash, hashedInput) == 0) {
                cout << "Account " << accId << " (" << name << ") deleted successfully.\n";
                deleted = true;
                continue;
            } else {
                cout << "Incorrect password. Deletion aborted.\n";
            }
        } 
        outFile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }

    inFile.close();
    outFile.close();

    if (!found) {
        remove("temp.dat");
        cout << "Account not found.\n";
        return;
    }

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
}

void Account::change_balence(int accid, char *sign, double amt) {
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    Account temp;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
        if (temp.accId == accid) {
            found = true;

            if (sign == "+") {
                temp.accBalance += amt;
            } else if (sign == "-") {
                if (temp.accBalance < amt) {
                    cout << "Insufficient balance. Operation aborted.\n";
                    break;
                }
                temp.accBalance -= amt;
            } else {
                cout << "Invalid sign. Use '+' to deposit or '-' to withdraw.\n";
                break;
            }

            file.seekp(-static_cast<int>(sizeof(temp)), ios::cur);
            file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
            file.flush();

            cout << "Balance updated. New balance for account " << accid << " is " << temp.accBalance << "\n";
            break;
        }
    }

    if (!found) {
        cout << "Account not found.\n";
    }

    file.close();
}

void Account::deleteAllAccounts() {
    ofstream file("accounts.dat", ios::binary | ios::trunc);
    if (!file) {
        cout << "Error opening accounts file.\n";
        return;
    }
    file.close();
    cout << "✅ All accounts have been permanently deleted.\n";
}

long long int Account::getID() { return accId; }
double Account::getBalance() { return accBalance; }
const char* Account::getName() { return name; }
