//  welcome.cpp
//
//  compile with welcome.h
//  2021-12-31 Rain Chen

#include "../include/welcome.h"
using namespace std;
//  show welcome messages
void Welcome::display_welcome() {
    cout << endl;
    cout << "\033[31m dP  oo  dP                                                \033[0m" << endl;
    cout << "\033[31m 88      88                                                \033[0m" << endl;
    cout << "\033[32m 88  dP  88d888b.  88d888b.  .d8888b.  88d888b.  dP    dP  \033[0m" << endl;
    cout << "\033[33m 88  88  88'  `88  88'  `88  88'  `88  88'  `88  88    88  \033[0m" << endl;
    cout << "\033[34m 88  88  88.  .88  88        88.  .88  88        88.  .88  \033[0m" << endl;
    cout << "\033[35m dP  dP  88Y8888'  dP        `88888P8  dP        `8888P88  \033[0m" << endl;
    cout << "\033[36m                                                      .88  \033[0m" << endl;
    cout << "\033[36m                                                  d8888P   \033[0m" << endl;
    return;
}
