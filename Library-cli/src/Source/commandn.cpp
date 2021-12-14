//
//  commandn.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/14.
//

#include "commandn.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

fstream bookn;
fstream profilen;
fstream nlog;

nudigiLibrary nbook[10000];
nuserprof nus[10000];

void commandn(string usr) {
    nulog(usr, "first");
    while (true) {
        cout << usr << "@digiLibrary ~ % ";
        string cmd;
        cin >> cmd;
        if (cmd == "quit") {
            //  quit this cli
            cout << "🍍 Goodbye!" << endl;
            nulog(usr, "quit");
            break;
        } else if (cmd == "help") {
            cout << "🍍 Welcome to digiLibrary. See the commands below:" << endl;
            cout << "Basic commands:" << endl;
            cout << "    'version' -- show current version." << endl;
            cout << "    'help' -- get help." << endl;
            cout << "    'quit' -- quit digiLibrary." << endl;
            cout << "Account settings:" << endl;
            cout << "    'passwd' -- change your password." << endl;
            cout << "Book Management:" << endl;
            cout << "    'listbook' -- list all the books." << endl;
            nulog(usr, "help");
        } else if (cmd == "version") {
            cout << "🍍 digiLibrary v1.0.0" << endl;
            cout << "Build Dec 2021." << endl;
            cout << "Made by Rain Chen and Zheng ShuYao." << endl;
            nulog(usr, "version");
        } else if (cmd == "listbook") {
            //  list all the books
            bookn.open("/Users/rainchen/digiLibrary/books.txt");
            int cnt = 0;
            while (bookn.eof() != 1) {
                bookn >> nbook[cnt].bname >> nbook[cnt].isbn >> nbook[cnt].author >> nbook[cnt].location >> nbook[cnt].borrow;
                cnt++;
            }
            cnt--;
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            for (int i = 0; i < cnt; i++) {
                cout << nbook[i].bname << " " << nbook[i].isbn << " " << nbook[i].author << " " << nbook[i].location << " " << nbook[i].borrow;
                cout << endl;
            }
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            nulog(usr, "listbook");
            cout << "🍍 All books listed. Done!" << endl;
        } else if (cmd == "passwd") {
            //  change password
            cout << "Loading profiles..." << endl;
            if (!(filesystem::exists("/Users/rainchen/digiLibrary/nuserinfo.digilib"))) {
                cout << "No current normal user. Initializing..." << endl;
                ofstream outfile("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                profilen.close();
            } else {
                profilen.open("/Users/rainchen/digiLibrary/nuserinfo.digilib");
            }
            int cnt = 0, mark = 0;
            while (profilen.eof() != 1) {
                profilen >> nus[cnt].nusername >> nus[cnt].npassword;
                if (usr == nus[cnt].nusername) {
                    mark = cnt;
                }
                cnt++;
            }
            cnt--;
            profilen.close();
            cout << "🍍 Ready." << endl;
            string newpass;
            cout << "Enter your new password:";
            cin >> newpass;
            profilen.open("/Users/rainchen/digiLibrary/nuserinfo.digilib", ios_base::out|ios_base::trunc);
            for (int i = 0; i < cnt; i++) {
                if (i == mark) {
                    profilen << nus[i].nusername << " " << newpass << endl;
                } else {
                    profilen << nus[i].nusername << " " << nus[i].npassword << endl;
                }
            }
            profilen.close();
            nulog(usr, "passwd");
            cout << "🍍 Done. Your password has been changed." << endl;
        }
    }
    return;
}

//  the log module -- write down the logs
int nulog(string usr, string command) {
    //  get time
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    //  is the log file existed
    if (!(filesystem::exists("/Users/rainchen/digiLibrary/digi.log"))) {
        cout << "Initializing log..." << endl;
        ofstream outfile("/Users/rainchen/digiLibrary/digi.log");
        nlog.close();
    }
    
    //  open log file
    nlog.open("/Users/rainchen/digiLibrary/digi.log", ios_base::app);
    
    //  print log
    if (command == "first") {
        nlog << "[" << tmp << "] " << "'" << usr << "' login." << endl;
    } else if (command == "help") {
        nlog << "[" << tmp << "] " << "'" << usr << "' show help." << endl;
    } else if (command == "quit") {
        nlog << "[" << tmp << "] " << "'" << usr << "' quit digiLibrary-cli." << endl;
    } else if (command == "listbook") {
        nlog << "[" << tmp << "] " << "'" << usr << "' show all books." << endl;
    } else if (command == "version") {
        nlog << "[" << tmp << "] " << "'" << usr << "' show version." << endl;
    } else if (command == "passwd") {
        nlog << "[" << tmp << "] " << "'" << usr << "' changed password." << endl;
    }
    
    //  close log file
    nlog.close();
    return 0;
}
