//  log4lib.cpp
//
//  compile with log4lib.h
//  2021-12-31 Rain Chen

#include "../include/log4lib.h"
//  namespace
using namespace std;
//  output log messages
fstream looog;
//  log module function
int log4lib(string user, string command, string data) {
    //  get time
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    //  log module
    string logdata = data + "/digi.log";
    ifstream fin(logdata);
    if (!fin) {
        fin.close();
        cout << "Log initializing..." << endl;
        ofstream outfile(logdata);
        outfile.close();
    }
    //  open log file
    looog.open(logdata, ios::app);
    if (command == "first") {
        looog << "[" << tmp << "] " << "'" << user << "' login." << endl;
    } else if (command == "quit") {
        looog << "[" << tmp << "] " << "'" << user << "' quit." << endl;
    } else if (command == "version") {
        looog << "[" << tmp << "] " << "'" << user << "' show version." << endl;
    } else if (command == "passwd") {
        looog << "[" << tmp << "] " << "'" << user << "' change password." << endl;
    } else if (command == "lsbook") {
        looog << "[" << tmp << "] " << "'" << user << "' list books." << endl;
    } else if (command == "search") {
        looog << "[" << tmp << "] " << "'" << user << "' search books." << endl;
    } else if (command == "lsuser") {
        looog << "[" << tmp << "] " << "'" << user << "' list users." << endl;
    } else if (command == "resetpwd") {
        looog << "[" << tmp << "] " << "'" << user << "' reset someone's password." << endl;
    } else if (command == "addbook") {
        looog << "[" << tmp << "] " << "'" << user << "' add a book." << endl;
    } else if (command == "clearlog") {
        looog << "[" << tmp << "] " << "'" << user << "' clear log." << endl;
    } else if (command == "delbook") {
        looog << "[" << tmp << "] " << "'" << user << "' remove a book." << endl;
    } else if (command == "lsborrow") {
        looog << "[" << tmp << "] " << "'" << user << "' see someone's borrowed books." << endl;
    } else if (command == "useradd") {
        looog << "[" << tmp << "] " << "'" << user << "' add a user." << endl;
    } else if (command == "userdel") {
        looog << "[" << tmp << "] " << "'" << user << "' remove a user." << endl;
    } else if (command == "lsmybook") {
        looog << "[" << tmp << "] " << "'" << user << "' list borrowed books." << endl;
    } else if (command == "borrow") {
        looog << "[" << tmp << "] " << "'" << user << "' borrow a book." << endl;
    } else if (command == "return") {
        looog << "[" << tmp << "] " << "'" << user << "' return a book." << endl;
    } else if (command == "stype") {
        looog << "[" << tmp << "] " << "'" << user << "' search books by types." << endl;
    }
    //  close log file
    looog.close();
    return 0;
}
