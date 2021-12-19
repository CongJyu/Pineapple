//
//  main.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/13.
//

//  !!! The book list must be in UTF-8 encoding !!!

//  header files
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <filesystem>

//  self-defined
#include "welcome.hpp"
#include "commands.hpp"
#include "commandn.hpp"
#include "log4me.hpp"

//  namespace std and some C++17 features
using namespace std;

//  the account structure -- store user accounts
struct accountInfo {
    string username;
    string password;
};

//  infile class -- read and write the files
fstream infile;

//  mode
int usrmode = 0;

//  application data and user data
string dir;

int main() {
    //  display welcome messages
    Welcome welcome;
    welcome.you();
    cout << "!~IMPORTANT~!" << endl;
    cout << "Configure your data dir(e.g. /Users/rainchen/digiLibrary):";
    cin >> dir;
    
    //  check the account info
    if (!(filesystem::exists(dir + "\\admininfo.digilib"))) {
        ofstream outfile(dir + "\\admininfo.digilib");
        infile.close();
        infile.open(dir + "\\admininfo.digilib");
        infile << "admin" << " " << "123456" << endl;
        infile.close();
        infile.open(dir + "\\admininfo.digilib");
        cout << "🍍 Restored admin account...\033[36mDone!\033[0m" << endl;
        cout << "Please login." << endl;
    } else {
        infile.open(dir + "\\admininfo.digilib");
        cout << "🍍 Checking...Done!" << endl;
        cout << "Please login." << endl;
    }
    
    //  read all user info
    accountInfo admin;
    infile >> admin.username >> admin.password;
    
    //  login
    string usr;
    string pwd;
    char login;
    cout << "'s' -- administrator" << endl;
    cout << "'n' -- normal user" << endl;
    cout << "root@digiLib ~ # ";
    cin >> login;
    while (login == 's') {
        cout << "USERNAME:";
        cin >> usr;
        cout << "PASSWORD:";
        cin >> pwd;
        if ((usr == admin.username) && (pwd == admin.password)) {
            cout << "🍍 Login successfully!" << endl;
            usrmode = 1;
            break;
        } else {
            cout << "ERR! Invalid username or password." << endl;
        }
    }
    infile.close();
    accountInfo nuser[10000];
    int cnt = 0;
    infile.open(dir + "\\nuserinfo.digilib");
    while (infile.eof() != 1) {
        infile >> nuser[cnt].username >> nuser[cnt].password;
        cnt++;
    }
    cnt--;
    while (login == 'n') {
        cout << "USERNAME:";
        cin >> usr;
        cout << "PASSWORD:";
        cin >> pwd;
        for (int i = 0; i < cnt; i++) {
            if ((usr == nuser[i].username) && (pwd == nuser[i].password)) {
                cout << "🍍 Login successfully!" << endl;
                usrmode = 2;
                break;
            } else {
                continue;
            }
        }
        //  if login successfully, quit login module
        if (usrmode == 2) {
            break;
        } else {
            cout << "ERR! Invalid username or password." << endl;
        }
    }
    infile.close();
    
    //  commandline input
    if (usrmode == 1) {
        //  SU command
        commands(usr, dir);
    } else if (usrmode == 2) {
        //  NU command
        commandn(usr, dir);
    } else {
        cout << "ERR! Unknown error." << endl;
    }
    return 0;
}
