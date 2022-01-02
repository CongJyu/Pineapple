//  account.cpp
//
//  compile with account.h
//  2021-12-31 Rain Chen

#include "../include/account.h"
using namespace std;
//  default constructor
Account::Account() {}
//  default destructor
Account::~Account() {}
//  login process
string Account::login(string accountdata) {
    cout << "USERNAME: \033[35m";
    cin >> temp_username;
    cout << "\033[0mPASSWORD: \033[35m";
    cin >> temp_password;
    cout << "\033[0m";
    fstream user_info;
    user_info.open(accountdata);
    user_info >> username >> password;
    user_info.close();
    while (temp_username != username || temp_password != password) {
        cout << "\033[41mERR! Wrong username or password. Try again please.\033[0m" << endl;
        cout << "USERNAME: \033[35m";
        cin >> temp_username;
        cout << "\033[0mPASSWORD: \033[35m";
        cin >> temp_password;
        cout << "\033[0m";
        if (temp_username == username && temp_password == password) {
            break;
        }
    }
    return temp_username;
}
//  school users login process
string Account::stulogin(string accountdata) {
    while (1) {
        cout << "USERNAME: \033[35m";
        cin >> temp_username;
        cout << "\033[0mPASSWORD: \033[35m";
        cin >> temp_password;
        cout << "\033[0m";
        fstream user_info;
        user_info.open(accountdata);
        long long cnt = 0;
        while (user_info.eof() != 1) {
            user_info >> username >> password;
            if (temp_username == username && temp_password == password) {
                cnt++;
                break;
            }
        }
        if (cnt != 0) {
            break;
        } else {
            cout << "\033[41mERR! Wrong username or password. Try again please.\033[0m" << endl;
        }
    }
    return temp_username;
}
//  change password
void Account::passwd(string dir) {
    string new_username, new_password;
    cout << "\033[35m";
    cin >> new_username >> new_password;
    cout << "\033[0m";
    fstream user_info;
    user_info.open(dir);
    user_info << new_username << " " << new_password;
    cout << "🍍 \033[36mDone. Username and password have been changed.\033[0m" << endl;
    return;
}
//  list school users
void Account::lsuser(string dir) {
    cout << "Loading..." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    fstream list;
    list.open(dir + "/nuserinfo.digilib");
    while (getline(list, userline)) {
        cout << userline << endl;
    }
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. All users listed.\033[0m" << endl;
    return;
}
//  reset someone's password
void Account::resetpwd(string dir) {
    string someone;
    cin >> someone;
    fstream resetp;
    cout << "Loading profiles..." << endl;
    resetp.open(dir + "/nuserinfo.digilib");
    long long mark = -1;
    ifstream countline;
    countline.open(dir + "/nuserinfo.digilib", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    Account * users = new Account [n];
    for (long long i = 0; i < n; i++) {
        resetp >> users[i].username >> users[i].password;
        if (users[i].username == someone) {
            mark = i;
        }
    }
    resetp.close();
    if (mark == -1) {
        cout << "🍍 \033[36mThere is no user '" << someone << "'. Done.\033[0m" << endl;
    } else {
        resetp.open(dir + "/nuserinfo.digilib", ios::out|ios::trunc);
        for (long long i = 0; i < n; i++) {
            if (i == mark) {
                resetp << users[i].username
                << " " << "123456" << endl;
            } else {
                resetp << users[i].username << " "
                << users[i].password << endl;
            }
        }
        resetp.close();
        cout << "🍍 \033[36m'" << someone << "' password reseted to default. Done.\033[0m" << endl;
    }
    delete [] users;
    return;
}
//  clear log
void Account::clog(string dir) {
    //  clear log info
    fstream cclog;
    ifstream fin(dir + "/digi.log");
    if (!fin) {
        fin.close();
        cout << "Profiles do not exist. Initializing..." << endl;
        ofstream outfile(dir + "/digi.log");
        outfile.close();
    }
    cclog.open(dir + "/digi.log", ios::out|ios::trunc);
    cclog.close();
    cout << "🍍 \033[36mDone. All log info cleared.\033[0m" << endl;
    return;
}
//  add a user
void Account::useradd(string dir) {
    fstream uadd;
    ifstream fin(dir + "/nuserinfo.digilib");
    if (!fin) {
        fin.close();
        cout << "No current normal user. Initializing..." << endl;
        ofstream outfile(dir + "/nuserinfo.digilib");
        outfile.close();
    } else {
        fin.close();
        cout << "Checking normal user profiles..." << endl;
    }
    string nusr, npwd;
    //  stand for 'normal user' and 'normal password'
    uadd.open(dir + "/nuserinfo.digilib", ios::app);
    cout << "New normal user:\033[35m";
    cin >> nusr;
    cout << "\033[0m'" << nusr << "' password:\033[35m";
    cin >> npwd;
    cout << "\033[0m";
    uadd << nusr << " " << npwd << endl;
    uadd.close();
    cout << "🍍 \033[36mNew user added! Done!\033[0m" << endl;
    return;
}
//  delete a user
void Account::userdel(string dir) {
    string targetuser;
    cin >> targetuser;
    fstream dele;
    ifstream fin(dir + "/nuserinfo.digilib");
    if (!fin) {
        fin.close();
        cout << "No current normal user. Initializing..." << endl;
        ofstream outfile(dir + "/nuserinfo.digilib");
        dele.close();
        cout << "🍍 \033[36mNo valid users. Done!\033[0m" << endl;
    } else {
        fin.close();
        cout << "Loading profiles..." << endl;
        long long n = 0;
        ifstream countline;
        string temp;
        countline.open(dir + "/nuserinfo.digilib", ios::in);
        while (getline(countline, temp, '\n')) {
            n++;
        }
        countline.close();
        dele.open(dir + "/nuserinfo.digilib");
        long long mark = -1;
        Account * uss = new Account [n];
        for (long long i = 0; i < n; i++) {
            dele >> uss[i].username >> uss[i].password;
            if (uss[i].username == targetuser) {
                mark = i;
            }
        }
        dele.close();
        if (mark == -1) {
            cout << "🍍 \033[36mThere is no user '" << targetuser << "'. Done.\033[0m" << endl;
        } else {
            dele.open(dir + "/nuserinfo.digilib", ios::out|ios::trunc);
            for (long long i = 0; i < n; i++) {
                if (i == mark) {
                    continue;
                } else {
                    dele << uss[i].username << " " << uss[i].password << endl;
                }
            }
            dele.close();
            cout << "🍍 \033[36mDone. '" << targetuser << "' is deleted.\033[0m" << endl;
        }
        delete [] uss;
    }
    return;
}

