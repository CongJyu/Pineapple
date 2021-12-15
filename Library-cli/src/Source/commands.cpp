//
//  commands.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/13.
//

#include "commands.hpp"
#include "log4me.hpp"
#include "countline.hpp"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

fstream checkbook;
fstream profile;

void commands(string usr) {
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
            //  helpful tips
            //  TODO: add 'delbook' command
            //  TODO: add 'chgbook' command
            cout << "🍍 Welcome to digiLibrary. See the commands below:" << endl;
            cout << "Basic commands:" << endl;
            cout << "    'version' -- show current version." << endl;
            cout << "    'help' -- get help." << endl;
            cout << "    'clearlog' -- clear log info." << endl;
            cout << "    'quit' -- quit digiLibrary." << endl;
            cout << "Account settings:" << endl;
            cout << "    'passwd' -- change and set your password." << endl;
            cout << "    'useradd' -- create a normal user." << endl;
            cout << "    'listuser' -- list all normal users." << endl;
            cout << "    'resetpwd' -- reset normal user's password to default." << endl;
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
            //  show version
            cout << "🍍 digiLibrary v1.0.0" << endl;
            cout << "Build Dec 2021." << endl;
            cout << "Made by Rain Chen and Zheng ShuYao." << endl;
            ulog(usr, "version");
        } else if (cmd == "listbook") {
            //  list all the books
            checkbook.open("/Users/rainchen/digiLibrary/books.txt");
            countline("/Users/rainchen/digiLibrary/books.txt");
            int cnt = countline("/Users/rainchen/digiLibrary/books.txt");
            digiLibrary * book = new digiLibrary [cnt];
            int j = 0;
            while (checkbook.eof() != 1) {
                checkbook >> book[j].bname
                >> book[j].isbn
                >> book[j].author
                >> book[j].location
                >> book[j].borrow;
                j++;
            }
            cnt = j - 1;
            checkbook.close();
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            for (int i = 0; i < cnt; i++) {
                cout << book[i].bname << " "
                << book[i].isbn << " "
                << book[i].author << " "
                << book[i].location << " "
                << book[i].borrow;
                cout << endl;
            }
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            delete [] book;
            ulog(usr, "listbook");
            cout << "🍍 All books listed. Done!" << endl;
        } else if (cmd == "passwd") {
            //  change username and password
            cout << "Loading profiles..." << endl;
            profile.open("/Users/rainchen/digiLibrary/admininfo.digilib");
            string oldusr, newusr, oldpwd, newpwd;
            profile >> oldusr >> oldpwd;
            profile.close();
            profile.open("/Users/rainchen/digiLibrary/admininfo.digilib", ios_base::out|ios_base::trunc);
            cout << "🍍 Done!" << endl;
            cout << "Enter your new username:";
            cin >> newusr;
            cout << "Enter your new password:";
            cin >> newpwd;
            profile << newusr << " " << newpwd;
            profile.close();
            ulog(usr, "passwd");
            cout << "🍍 Profile updated!" << endl;
            cout << "Use your new username and password to login next time." << endl;
        } else if (cmd == "useradd") {
            //  add a normal user
            if (!(filesystem::exists("/Users/rainchen/digiLibrary/nuserinfo.digilib"))) {
                cout << "No current normal user. Initializing..." << endl;
                ofstream outfile("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                profile.close();
            } else {
                cout << "Checking normal user profiles..." << endl;
            }
            string nusr, npwd;
            //  stand for 'normal user' and 'normal password'
            profile.open("/Users/rainchen/digiLibrary/nuserinfo.digilib", ios_base::app);
            cout << "New normal user:";
            cin >> nusr;
            cout << "'" << nusr << "' password:";
            cin >> npwd;
            profile << nusr << " " << npwd << endl;
            profile.close();
            ulog(usr, "useradd");
            cout << "🍍 New normal user added! Done!" << endl;
        } else if (cmd == "listuser") {
            //  list all normal users, not super users
            if (!(filesystem::exists("/Users/rainchen/digiLibrary/nuserinfo.digilib"))) {
                cout << "No current normal user. Initializing..." << endl;
                ofstream outfile("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                profile.close();
                ulog(usr, "listuser");
                cout << "🍍 No valid users. Done!" << endl;
            } else {
                profile.open("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                int cnt = countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                nusProfile * users = new nusProfile [cnt];
                for (int i = 0; i < cnt; i++) {
                    profile >> users[i].nusername >> users[i].npassword;
                }
                profile.close();
                for (int i = 0; i < 80; i++) {
                    cout << "-";
                }
                cout << endl;
                for (int i = 0; i < cnt; i++) {
                    cout << users[i].nusername << "    *******" << endl;
                }
                for (int i = 0; i < 80; i++) {
                    cout << "-";
                }
                cout << endl;
                ulog(usr, "listuser");
                delete [] users;
                cout << "🍍 " << cnt << " user(s) in total. Done!" << endl;
            }
        } else if (cmd == "resetpwd") {
            //  set specific normal user's password to default
            if (!(filesystem::exists("/Users/rainchen/digiLibrary/nuserinfo.digilib"))) {
                cout << "No current normal user. Initializing..." << endl;
                ofstream outfile("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                profile.close();
                ulog(usr, "resetpwd");
                cout << "🍍 No valid users. Done!" << endl;
            } else {
                //  reset user -- the username whose password will be reset
                string resetuser;
                cout << "Loading profiles..." << endl;
                profile.open("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                cout << "Done. Reset whose password(Enter username):";
                cin >> resetuser;
                int mark = 0;
                countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                int cnt = countline("/Users/rainchen/digiLibrary/nuserinfo.digilib");
                nusProfile * users = new nusProfile [cnt];
                for (int i = 0; i < cnt; i++) {
                    profile >> users[i].nusername >> users[i].npassword;
                    if (users[i].nusername == resetuser) {
                        mark = i;
                    }
                }
                profile.close();
                if (mark == 0) {
                    ulog(usr, "resetpwd");
                    cout << "🍍 There is no user '" << resetuser << "'. Done." << endl;
                } else {
                    profile.open("/Users/rainchen/digiLibrary/nuserinfo.digilib", ios_base::out|ios_base::trunc);
                    for (int i = 0; i < cnt; i++) {
                        if (i == mark) {
                            profile << users[i].nusername
                            << " " << "123456" << endl;
                        } else {
                            profile << users[i].nusername << " "
                            << users[i].npassword << endl;
                        }
                    }
                    profile.close();
                    ulog(usr, "resetpwd");
                    cout << "🍍 '" << resetuser << "' password reseted to default. Done." << endl;
                }
                delete [] users;
            }
        } else if (cmd == "addbook") {
            //  enter full command here
            string newbookname, newbookisbn, newbookauthor;
            string newbooklocation, newbookborrow;
            cin >> newbookname
            >> newbookisbn
            >> newbookauthor
            >> newbooklocation;
            cin >> newbookborrow;
            //  open book list
            checkbook.open("/Users/rainchen/digiLibrary/books.txt", ios_base::app);
            checkbook << newbookname << " "
            << newbookisbn << " "
            << newbookauthor << " "
            << newbooklocation << " "
            << newbookborrow << endl;
            checkbook.close();
            ulog(usr, "addbook");
            cout << "🍍 " << "Done. The book '" << newbookname << "' is added." << endl;
        } else if (cmd == "clearlog") {
            //  clear log info
            if (!(filesystem::exists("/Users/rainchen/digiLibrary/digi.log"))) {
                cout << "No current log info. Initializing..." << endl;
                //  create the log file
                ofstream outfile("/Users/rainchen/digiLibrary/digi.log");
                profile.close();
            }
            profile.open("/Users/rainchen/digiLibrary/digi.log", ios_base::out|ios_base::trunc);
            profile.close();
            ulog(usr, "clearlog");
            cout << "🍍 Done. All log info cleared." << endl;
        } else if (cmd == "search") {
            //  search books
            cout << "Loading books...";
            char c[2];    //  receive command
            checkbook.open("/Users/rainchen/digiLibrary/books.txt");
            countline("/Users/rainchen/digiLibrary/books.txt");
            int cnt = countline("/Users/rainchen/digiLibrary/books.txt");
            digiLibrary * book = new digiLibrary [cnt];
            int j = 0;
            while (checkbook.eof() != 1) {
                checkbook >> book[j].bname
                >> book[j].isbn
                >> book[j].author
                >> book[j].location
                >> book[j].borrow;
                j++;
            }
            cnt = j - 1;
            checkbook.close();
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
                        if (book[i].bname.find(searchbook) != string::npos) {
                            cout << book[i].bname << " "
                            << book[i].isbn << " "
                            << book[i].author << " "
                            << book[i].location << " "
                            << book[i].borrow << endl;
                        }
                    }
                    break;
                case 'i':
                    for (int i = 0; i < cnt; i++) {
                        if (book[i].isbn.find(searchbook) != string::npos) {
                            cout << book[i].bname << " "
                            << book[i].isbn << " "
                            << book[i].author << " "
                            << book[i].location << " "
                            << book[i].borrow << endl;
                        }
                    }
                    break;
                case 'a':
                    for (int i = 0; i < cnt; i++) {
                        if (book[i].author.find(searchbook) != string::npos) {
                            cout << book[i].bname << " "
                            << book[i].isbn << " "
                            << book[i].author << " "
                            << book[i].location << " "
                            << book[i].borrow << endl;
                        }
                    }
                    break;
            }
            for (int i = 0; i < 80; i++) {
                cout << "-";
            }
            cout << endl;
            delete [] book;
            cout << "🍍 Searching done. The results are listed above." << endl;
        }
    }
    return;
}
