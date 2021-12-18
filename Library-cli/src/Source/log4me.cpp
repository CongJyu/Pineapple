//
//  log4me.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/14.
//

#include "log4me.hpp"
#include <ctime>

using namespace std;

fstream log;

//  the log module -- write down the logs
int ulog(string usr, string command) {
    //  get time
    time_t timep;
    time(&timep);
    char tmp[256];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    //  is the log file existed
    if (!(filesystem::exists("/Users/rainchen/digiLibrary/digi.log"))) {
        cout << "Initializing log..." << endl;
        ofstream outfile("/Users/rainchen/digiLibrary/digi.log");
        log.close();
    }
    
    //  open log file
    log.open("/Users/rainchen/digiLibrary/digi.log", ios_base::app);
    
    //  print log
    if (command == "first") {
        log << "[" << tmp << "] " << "'" << usr << "' login." << endl;
    } else if (command == "help") {
        log << "[" << tmp << "] " << "'" << usr << "' show help." << endl;
    } else if (command == "quit") {
        log << "[" << tmp << "] " << "'" << usr << "' quit digiLibrary-cli." << endl;
    } else if (command == "passwd") {
        log << "[" << tmp << "] " << "'" << usr << "' change username and password." << endl;
    } else if (command == "useradd") {
        log << "[" << tmp << "] " << "'" << usr << "' add a normal user." << endl;
    } else if (command == "listuser") {
        log << "[" << tmp << "] " << "'" << usr << "' show all normal users." << endl;
    } else if (command == "resetpwd") {
        log << "[" << tmp << "] " << "'" << usr << "' reset a normal user's password." << endl;
    } else if (command == "listbook") {
        log << "[" << tmp << "] " << "'" << usr << "' show all books." << endl;
    } else if (command == "version") {
        log << "[" << tmp << "] " << "'" << usr << "' show version." << endl;
    } else if (command == "addbook") {
        log << "[" << tmp << "] " << "'" << usr << "' add a book." << endl;
    } else if (command == "clearlog") {
        log << "[" << tmp << "] " << "'" << usr << "' clear log info." << endl;
    } else if (command == "search") {
        log << "[" << tmp << "] " << "'" << usr << "' search books." << endl;
    } else if (command == "delbook") {
        log << "[" << tmp << "] " << "'" << usr << "' delete a book." << endl;
    }
    
    //  close log file
    log.close();
    return 0;
}
