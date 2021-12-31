//  account.h
//
//  account profile processing
//  2021-12-31 Rain Chen

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <filesystem>
#include <unistd.h>

using namespace std;

class Account {
private:
    string username;
    string password;
    string temp_username;
    string temp_password;
    string userline;
public:
    Account();
    ~Account();
    string login(string);
    string stulogin(string);
    void passwd(string);
    void lsuser(string);
    void resetpwd(string);
    void clog(string);
    void useradd(string);
    void userdel(string);
};

#endif
