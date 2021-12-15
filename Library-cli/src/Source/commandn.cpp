//
//  commandn.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/14.
//

#include "commandn.hpp"
#include "log4me.hpp"
#include "countline.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

fstream bookn;
fstream profilen;

void commandn(string usr) {
    ulog(usr, "first");
    while (true) {
        cout << usr << "@digiLibrary ~ 😅 ";
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
            countline("/Users/rainchen/digiLibrary/books.txt");
            int cnt = countline("/Users/rainchen/digiLibrary/books.txt");
            nudigiLibrary * nbook = new nudigiLibrary [cnt];
            int j = 0;
            while (bookn.eof() != 1) {
                bookn >> nbook[j].bname
                >> nbook[j].isbn
                >> nbook[j].author
                >> nbook[j].location
                >> nbook[j].borrow;
                j++;
            }
            cnt = j - 1;
            bookn.close();
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            for (int i = 0; i < cnt; i++) {
                cout << nbook[i].bname << " "
                << nbook[i].isbn << " "
                << nbook[i].author << " "
                << nbook[i].location << " "
                << nbook[i].borrow;
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
            int mark = 0;
            countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
            int cnt = countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
            nuserprof * nus = new nuserprof [cnt];
            for (int i = 0; i < cnt; i++) {
                profilen >> nus[i].nusername >> nus[i].npassword;
                if (usr == nus[i].nusername) {
                    mark = i;
                }
            }
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
            delete [] nus;
            cout << "🍍 Done. Your password has been changed." << endl;
        } else if (cmd == "search") {
            //  search books
            cout << "Loading books...";
            char c[2];    //  receive command
            bookn.open("/Users/rainchen/digiLibrary/books.txt");
            countline("/Users/rainchen/digiLibrary/books.txt");
            int cnt = countline("/Users/rainchen/digiLibrary/books.txt");
            nudigiLibrary * nbook = new nudigiLibrary [cnt];
            int j = 0;
            while (bookn.eof() != 1) {
                bookn >> nbook[j].bname
                >> nbook[j].isbn
                >> nbook[j].author
                >> nbook[j].location
                >> nbook[j].borrow;
                j++;
            }
            cnt = j - 1;
            bookn.close();
            cout << "Ready." << endl;
            string searchbook;
            cin >> c;
            cout << "Searching..." << endl;
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cin >> searchbook;
            cout << endl;
            switch (c[1]) {
                case 'n':
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].bname.find(searchbook) != string::npos) {
                            cout << nbook[i].bname << " "
                            << nbook[i].isbn << " "
                            << nbook[i].author << " "
                            << nbook[i].location << " "
                            << nbook[i].borrow << endl;
                        }
                    }
                    break;
                case 'i':
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].isbn.find(searchbook) != string::npos) {
                            cout << nbook[i].bname << " "
                            << nbook[i].isbn << " "
                            << nbook[i].author << " "
                            << nbook[i].location << " "
                            << nbook[i].borrow << endl;
                        }
                    }
                    break;
                case 'a':
                    for (int i = 0; i < cnt; i++) {
                        if (nbook[i].author.find(searchbook) != string::npos) {
                            cout << nbook[i].bname << " "
                            << nbook[i].isbn << " "
                            << nbook[i].author << " "
                            << nbook[i].location << " "
                            << nbook[i].borrow << endl;
                        }
                    }
                    break;
            }
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            delete [] nbook;
            cout << "🍍 Searching done. The results are listed above." << endl;
        }
    }
    return;
}
