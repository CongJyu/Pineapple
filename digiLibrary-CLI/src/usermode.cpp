//  usermode.cpp
//
//  judging usermode
//  2021-12-31 Rain Chen

#include "../include/usermode.h"
//  namespace
using namespace std;
//  judge user's mode
int judge_usermode() {
    cout << "Choose your account type:" << endl;
    cout << "'s' -- Administrator, or" << endl;
    cout << "'n' -- School users" << endl;
    cout << "root@digiLibrary ~ # ";
    char mode;
    cin >> mode;
    if (mode == 's') {
        return 1;
    } else if (mode == 'n') {
        return 2;
    } else {
        return 0;
    }
}
