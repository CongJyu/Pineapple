//  main.cpp
//
//  this is the main process of digiLibrary
//  2021-12-31 Rain Chen

//  !!! the "books.txt" file must be UTF-8 encoding !!!
#include "../include/welcome.h"
#include "../include/account.h"
#include "../include/usermode.h"
#include "../include/log4lib.h"
#include "../include/book.h"
//  using namespace, use some C++ 17 features
using namespace std;
//  account file processing
fstream account;
//  user dir
string dir_location;
//  main process
int main() {
    //  show welcome messages
    Welcome you;
    you.display_welcome();
    //  config user data dir
    cout << "\033[36m!~IMPORTANT~!\033[0m" << endl;
    cout << "Configure your data dir(e.g. /Users/rainchen/Documents/digiLibrary):";
    cin >> dir_location;
    //  choose your user mode
    int usermode = judge_usermode();
    if (usermode == 1) {
        string accountdata = dir_location + "/admininfo.digilib";
        ifstream fin(accountdata);
        if (!fin) {
            //  if file do not exist, create and initialize
            fin.close();
            cout << "Profiles do not exist. Initializing..." << endl;
            ofstream outfile(accountdata);
            account.close();
            account.open(accountdata);
            account << "admin"
                    << " "
                    << "123456" << endl;
            account.close();
            cout << "Restored admin account...\033[36mDone!\033[0m" << endl;
            cout << "Please login." << endl;
        } else {
            //  if exist, open
            fin.close();
            cout << "Checking...\033[36mDone!\033[0m" << endl;
            cout << "Please login." << endl;
        }
        Account admin;
        string username = admin.login(accountdata);
        //  user commands
        log4lib(username, "first", dir_location);
        while (1) {
            Book control;
            cout << username << "@digiLibrary ~ # \033[35m";
            string cmd;
            cin >> cmd;
            cout << "\033[0m";
            if (cmd == "help") {
                //  seek for help
                log4lib(username, "help", dir_location);
                control.help();
            } else if (cmd == "quit") {
                //  quit this program
                log4lib(username, "quit", dir_location);
                control.quit();
                break;
            } else if (cmd == "version") {
                //  show version information
                log4lib(username, "version", dir_location);
                control.version();
            } else if (cmd == "passwd") {
                //  change password
                log4lib(username, "passwd", dir_location);
                admin.passwd(accountdata);
            } else if (cmd == "lsbook") {
                //  list all books
                log4lib(username, "lsbook", dir_location);
                control.lsbook(dir_location);
            } else if (cmd == "search") {
                //  search some books
                log4lib(username, "search", dir_location);
                control.search(dir_location);
            } else if (cmd == "lsuser") {
                //  list all school users
                log4lib(username, "lsuser", dir_location);
                admin.lsuser(dir_location);
            } else if (cmd == "resetpwd") {
                //  reset someone's password
                log4lib(username, "resetpwd", dir_location);
                admin.resetpwd(dir_location);
            } else if (cmd == "clearlog") {
                //  clear log
                admin.clog(dir_location);
                log4lib(username, "clearlog", dir_location);
            } else if (cmd == "delbook") {
                //  delete a book
                log4lib(username, "delbook", dir_location);
                control.delbook(dir_location);
            } else if (cmd == "addbook") {
                //  add a book
                log4lib(username, "addbook", dir_location);
                control.addbook(dir_location);
            } else if (cmd == "lsborrow") {
                //  show someone's borrowed books
                log4lib(username, "lsborrow", dir_location);
                control.lsborrow(dir_location);
            } else if (cmd == "useradd") {
                //  add a user
                log4lib(username, "useradd", dir_location);
                admin.useradd(dir_location);
            } else if (cmd == "userdel") {
                //  delete a user
                log4lib(username, "userdel", dir_location);
                admin.userdel(dir_location);
            } else if (cmd == "lsmybook") {
                //  list books i borrowed
                //  log4lib(username, "lsmybook", dir_location);
                //  control.lsmybook(dir_location, username);
                cout << "\033[41mERR! Administrator cannot borrow or return books.\033[0m" << endl;
            } else if (cmd == "borrow") {
                //  borrow a book from library
                //  log4lib(username, "borrow", dir_location);
                //  control.borrow(dir_location, username);
                cout << "\033[41mERR! Administrator cannot borrow or return books.\033[0m" << endl;
            } else if (cmd == "return") {
                //  borrow a book from library
                //  log4lib(username, "return", dir_location);
                //  control.returnbook(dir_location, username);
                cout << "\033[41mERR! Administrator cannot borrow or return books.\033[0m" << endl;
            } else if (cmd == "stype") {
                //  search books by types
                log4lib(username, "stype", dir_location);
                control.stype(dir_location);
            } else if (cmd == "import") {
                //  search books by types
                log4lib(username, "import", dir_location);
                control.import(dir_location);
            } else {
                //  unknown commands
                cout << "\033[41mERR! Unknown command '" << cmd << "'.\033[0m" << endl;
                cout << "Type 'help' to see user guides." << endl;
            }
        }
    } else if (usermode == 2) {
        string accountdata = dir_location + "/nuserinfo.digilib";
        ifstream fin(accountdata);
        if (!fin) {
            //  if file do not exist, create and initialize
            fin.close();
            cout << "Profiles do not exist. Initializing..." << endl;
            ofstream outfile(accountdata);
            account.close();
            account.open(accountdata);
            account.close();
            cout << "Restored admin account...\033[36mDone!\033[0m" << endl;
            cout << "Please login." << endl;
        } else {
            //  if exist, open
            fin.close();
            cout << "Checking...\033[36mDone!\033[0m" << endl;
            cout << "Please login." << endl;
        }
        Account students;
        string username = students.stulogin(accountdata);
        //  user commands
        while (1) {
            Book stu;
            cout << username << "@digiLibrary ~ % \033[35m";
            string cmd;
            cin >> cmd;
            cout << "\033[0m";
            if (cmd == "help") {
                //  seek for help
                log4lib(username, "help", dir_location);
                stu.help();
            } else if (cmd == "quit") {
                //  quit this program
                log4lib(username, "quit", dir_location);
                stu.quit();
                break;
            } else if (cmd == "version") {
                //  show version information
                log4lib(username, "version", dir_location);
                stu.version();
            } else if (cmd == "passwd") {
                //  change password
                log4lib(username, "passwd", dir_location);
                students.passwd(accountdata);
            } else if (cmd == "lsbook") {
                //  list all books
                log4lib(username, "lsbook", dir_location);
                stu.lsbook(dir_location);
            } else if (cmd == "search") {
                //  search some books
                log4lib(username, "search", dir_location);
                stu.search(dir_location);
            } else if (cmd == "lsuser") {
                //  list all school users
                //  log4lib(username, "lsuser", dir_location);
                //  students.lsuser(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "resetpwd") {
                //  reset someone's password
                log4lib(username, "resetpwd", dir_location);
                students.resetpwd(dir_location);
            } else if (cmd == "clearlog") {
                //  clear log
                //  students.clog(dir_location);
                //  log4lib(username, "clearlog", dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "delbook") {
                //  delete a book
                //  log4lib(username, "delbook", dir_location);
                //  stu.delbook(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "addbook") {
                //  add a book
                //  log4lib(username, "addbook", dir_location);
                //  stu.addbook(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "lsborrow") {
                //  show someone's borrowed books
                //  log4lib(username, "lsborrow", dir_location);
                //  stu.lsborrow(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "useradd") {
                //  add a user
                //  log4lib(username, "useradd", dir_location);
                //  students.useradd(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "userdel") {
                //  delete a user
                //  log4lib(username, "userdel", dir_location);
                //  students.userdel(dir_location);
                cout << "\033[41mERR! You must be a administrator to use this command.\033[0m" << endl;
            } else if (cmd == "lsmybook") {
                //  list books i borrowed
                log4lib(username, "lsmybook", dir_location);
                stu.lsmybook(dir_location, username);
            } else if (cmd == "borrow") {
                //  borrow a book from library
                log4lib(username, "borrow", dir_location);
                stu.borrow(dir_location, username);
            } else if (cmd == "return") {
                //  borrow a book from library
                log4lib(username, "return", dir_location);
                stu.returnbook(dir_location, username);
            } else if (cmd == "stype") {
                //  search books by types
                log4lib(username, "stype", dir_location);
                stu.stype(dir_location);
            } else {
                //  unknown commands
                cout << "\033[41mERR! Unknown command '" << cmd << "'.\033[0m" << endl;
                cout << "Type 'help' to see user guides." << endl;
            }
        }
    } else {
        //  wrong aommand
        cout << "\033[41mERR! Unknown error.\033[0m" << endl;
    }
    return 0;
}
