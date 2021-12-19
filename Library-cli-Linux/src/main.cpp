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
#include "../include/welcome.hpp"
#include "../include/commands.hpp"
#include "../include/commandn.hpp"
#include "../include/log4me.hpp"

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
    cout << "\033[36m!~IMPORTANT~!\033[0m" << endl;
    cout << "Configure your data dir(e.g. /Users/rainchen/digiLibrary):";
    cin >> dir;
    
    //  check the account info
    if (!(filesystem::exists(dir + "/admininfo.digilib"))) {
        ofstream outfile(dir + "/admininfo.digilib");
        infile.close();
        infile.open(dir + "/admininfo.digilib");
        infile << "admin" << " " << "123456" << endl;
        infile.close();
        infile.open(dir + "/admininfo.digilib");
        cout << "🍍 Restored admin account...\033[36mDone!\033[0m" << endl;
        cout << "Please login." << endl;
    } else {
        infile.open(dir + "/admininfo.digilib");
        cout << "🍍 Checking...\033[36mDone!\033[0m" << endl;
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
    cout << "\033[35m";
    cin >> login;
    cout << "\033[0m";
    while (login == 's') {
        cout << "USERNAME:\033[35m";
        cin >> usr;
        cout << "\033[0mPASSWORD:\033[35m";
        cin >> pwd;
        cout << "\033[0m";
        if ((usr == admin.username) && (pwd == admin.password)) {
            cout << "🍍 \033[36mLogin successfully!\033[0m" << endl;
            usrmode = 1;
            break;
        } else {
            cout << "\033[41mERR! Invalid username or password.\033[0m" << endl;
        }
    }
    infile.close();
    accountInfo nuser[10000];
    int cnt = 0;
    infile.open(dir + "/nuserinfo.digilib");
    while (infile.eof() != 1) {
        infile >> nuser[cnt].username >> nuser[cnt].password;
        cnt++;
    }
    cnt--;
    while (login == 'n') {
        cout << "USERNAME:\033[35m";
        cin >> usr;
        cout << "\033[0mPASSWORD:\033[35m";
        cin >> pwd;
        cout << "\033[0m";
        for (int i = 0; i < cnt; i++) {
            if ((usr == nuser[i].username) && (pwd == nuser[i].password)) {
                cout << "🍍 \033[36mLogin successfully!\033[0m" << endl;
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
            cout << "\033[41mERR! Invalid username or password.\033[0m" << endl;
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
        cout << "\033[41mERR! Unknown error.\033[0m" << endl;
    }
    return 0;
}
