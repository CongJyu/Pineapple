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
#include <unistd.h>

using namespace std;

fstream bookn;
fstream profilen;

void show_user_help();

void commandn(string usr, string dir) {
    ulog(usr, "first");
    while (true) {
        //  is user data existes
        string userpath = dir + "/" + usr + ".digidata";
        if (!(filesystem::exists(userpath))) {
            ofstream outfile(userpath);
            outfile.close();
            profilen.open(userpath);
            profilen.close();
        } else {
            profilen.open(userpath);
            profilen.close();
        }
        cout << usr << "@digiLibrary ~ % ";
        cout << "\033[35m";
        string cmd;
        cin >> cmd;
        cout << "\033[0m";
        if (cmd == "quit") {
            //  quit this cli
            cout << "🍍 \033[36mGoodbye!\033[0m" << endl;
            ulog(usr, "quit");
            break;
        } else if (cmd == "help") {
            //  show help
            show_user_help();
            ulog(usr, "help");
        } else if (cmd == "version") {
            for (int i = 0; i < 80; i++) {
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            cout << "🍍 digiLibrary v1.0.0" << endl;
            cout << "Build Dec 2021." << endl;
            cout << "Made by Rain Chen and Zheng ShuYao." << endl;
            for (int i = 0; i < 80; i++) {
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            ulog(usr, "version");
        } else if (cmd == "listbook") {
            //  list all the books
            bookn.open(dir + "/books.txt");
            countline(dir + "/books.txt");
            int cnt = countline(dir + "/books.txt");
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
                cout << "\033[36m-\033[0m";
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
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            ulog(usr, "listbook");
            cout << "🍍 \033[36mAll books listed. Done!\033[0m" << endl;
        } else if (cmd == "passwd") {
            //  change password
            cout << "Loading profiles..." << endl;
            if (!(filesystem::exists(dir + "/nuserinfo.digilib"))) {
                cout << "No current normal user. Initializing..." << endl;
                ofstream outfile(dir + "/nuserinfo.digilib");
                profilen.close();
            } else {
                profilen.open(dir + "/nuserinfo.digilib");
            }
            int mark = 0;
            countline(dir + "/nuserinfo.digilib");
            int cnt = countline(dir + "/nuserinfo.digilib");
            nuserprof * nus = new nuserprof [cnt];
            for (int i = 0; i < cnt; i++) {
                profilen >> nus[i].nusername >> nus[i].npassword;
                if (usr == nus[i].nusername) {
                    mark = i;
                }
            }
            profilen.close();
            cout << "🍍 \033[36mReady.\033[0m" << endl;
            string newpass;
            cout << "Enter your new password:";
            cin >> newpass;
            profilen.open(dir + "/nuserinfo.digilib", ios_base::out|ios_base::trunc);
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
            cout << "🍍 \033[36mDone. Your password has been changed.\033[0m" << endl;
        } else if (cmd == "search") {
            //  search books
            cout << "Loading books...";
            char c[2];    //  receive command
            bookn.open(dir + "/books.txt");
            countline(dir + "/books.txt");
            int cnt = countline(dir + "/books.txt");
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
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            cin >> searchbook;
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
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            delete [] nbook;
            ulog(usr, "search");
            cout << "🍍 \033[36mSearching done. The results are listed above.\033[0m" << endl;
        } else if (cmd == "borrow") {
            string borrowbook;
            cin >> borrowbook;
            bookn.open(dir + "/books.txt");
            countline(dir + "/books.txt");
            int cnt = countline(dir + "/books.txt");
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
            string userpath = dir + "/" + usr + ".digidata";
            bookn.open(userpath, ios_base::app);
            for (int i = 0; i < cnt; i++) {
                if (nbook[i].isbn == borrowbook) {
                    bookn << nbook[i].bname << " "
                    << nbook[i].isbn << " "
                    << nbook[i].author << " "
                    << nbook[i].location << " "
                    << nbook[i].borrow << endl;
                    break;
                }
            }
            delete [] nbook;
            bookn.close();
            ulog(usr, "borrow");
            cout << "🍍 \033[36mDone. Borrow '" << borrowbook << "' from library.\033[0m" << endl;
        } else if (cmd == "return") {
            string returnbook;
            cin >> returnbook;
            string userpath = dir + "/" + usr + ".digidata";
            bookn.open(userpath);
            int cnt = countline(userpath);
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
            bookn.open(userpath, ios_base::out|ios_base::trunc);
            for (int i = 0; i < cnt; i++) {
                if (nbook[i].isbn == returnbook) {
                    continue;
                } else {
                    bookn << nbook[i].bname << " "
                    << nbook[i].isbn << " "
                    << nbook[i].author << " "
                    << nbook[i].location << " "
                    << nbook[i].borrow << endl;
                }
            }
            bookn.close();
            ulog(usr, "return");
            cout << "🍍 \033[36mDone. Return '" << returnbook << "' to library.\033[0m" << endl;
        } else if (cmd == "lsmybook") {
            //  list the books you've borrowed
            cout << "Loading books..." << endl;
            bookn.open(dir + "/" + usr + ".digidata");
            countline(dir + "/" + usr + ".digidata");
            int cnt = countline(dir + "/" + usr + ".digidata");
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
            cout << "Current books you've borrowed:" << endl;
            for (int i = 0; i < 80; i++) {
                cout << "\033[36m-\033[0m";
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
                cout << "\033[36m-\033[0m";
            }
            cout << endl;
            delete [] nbook;
            ulog(usr, "lsmybook");
            cout << "🍍 \033[36mDone. All your books are listed." << endl;
            cout << "Do not forget to return them on time.\033[0m" << endl;
        } else {
            cout << "\033[41mERR! Unknown command '" << cmd << "'.\033[0m" << endl;
            cout << "Type 'help' to see user guides." << endl;
        }
    }
    return;
}

void show_user_help() {
    cout << "🍍 Welcome to digiLibrary. See the commands below:" << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
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
    cout << "    'borrow <ISBN/ISSN>' -- borrow a book from library." << endl;
    cout << "    'return <ISBN/ISSN>' -- return a book to library." << endl;
    cout << "    'lsmybook' -- list the books you've borrowed." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    return;
}
