//
//  commandn.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/14.
//

#include "commandn.hpp"
#include "log4me.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

fstream bookn;
fstream profilen;

nudigiLibrary nbook[10000];
nuserprof nus[10000];

void commandn(string usr) {
    ulog(usr, "first");
    while (true) {
        cout << usr << "@digiLibrary ~ % ";
        string cmd;
        cin >> cmd;
        if (cmd == "quit") {
            //  quit this cli
            cout << "🍍 Goodbye!" << endl;
            ulog(usr, "quit");
            break;
        } else if (cmd == "help") {
            cout << "🍍 Welcome to digiLibrary. See the commands below:" << endl;
            cout << "Basic commands:" << endl;
            cout << "    'version' -- show current version." << endl;
            cout << "    'help' -- get help." << endl;
            cout << "    'quit' -- quit digiLibrary." << endl;
            cout << "Account settings:" << endl;
            cout << "    'passwd' -- change and set your password." << endl;
            cout << "Book Management:" << endl;
            cout << "    'listbook' -- list all the books." << endl;
            cout << "    'addbook <Bookname> <ISBN/ISSN> <Author> <Class> <isBorrow>' -- add a book to library." << endl;
            cout << "    'search' -- search a book from library." << endl;
            cout << "        'search -n <Bookname>'" << endl;
            cout << "        'search -i <ISBN/ISSN>'" << endl;
            cout << "        'search -a <Author>'" << endl;
            cout << "        'search -l <Class>'" << endl;
            ulog(usr, "help");
        } else if (cmd == "version") {
            cout << "🍍 digiLibrary v1.0.0" << endl;
            cout << "Build Dec 2021." << endl;
            cout << "Made by Rain Chen and Zheng ShuYao." << endl;
            ulog(usr, "version");
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
            ulog(usr, "listbook");
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
            ulog(usr, "passwd");
            cout << "🍍 Done. Your password has been changed." << endl;
        } else if (cmd == "search") {
            //  search books
            cout << "Loading books...";
            char c[2];    //  receive command
            bookn.open("/Users/rainchen/digiLibrary/books.txt");
            int cnt = 0;
            while (bookn.eof() != 1) {
                bookn >> nbook[cnt].bname >> nbook[cnt].isbn >> nbook[cnt].author >> nbook[cnt].location >> nbook[cnt].borrow;
                cnt++;
            }
            cnt--;    //  fix the number of books, remove the impact of empty line
            cout << "Ready." << endl;
            string searchbookname;
            string searchbookisbn;
            string searchbookauth;
            cin >> c;
            cout << "Searching..." << endl;
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            switch (c[1]) {
                case 'n':
                    cin >> searchbookname;
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].bname.find(searchbookname) != string::npos) {
                            cout << nbook[i].bname << " " << nbook[i].isbn << " " << nbook[i].author << " " << nbook[i].location << " " << nbook[i].borrow << endl;
                        }
                    }
                    break;
                case 'i':
                    cin >> searchbookisbn;
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].isbn.find(searchbookisbn) != string::npos) {
                            cout << nbook[i].bname << " " << nbook[i].isbn << " " << nbook[i].author << " " << nbook[i].location << " " << nbook[i].borrow << endl;
                        }
                    }
                    break;
                case 'a':
                    cin >> searchbookauth;
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].author.find(searchbookauth) != string::npos) {
                            cout << nbook[i].bname << " " << nbook[i].isbn << " " << nbook[i].author << " " << nbook[i].location << " " << nbook[i].borrow << endl;
                        }
                    }
                    break;
            }
            bookn.close();
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            ulog(usr, "search");
            cout << "🍍 Searching done. The results are listed above." << endl;
        }
    }
    return;
}
