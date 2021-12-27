//
//  countline.cpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/15.
//

#include "../include/countline.hpp"
//  countline function
int countline(string filename) {
    ifstream countline;
    countline.open(filename, ios::in);
    string temp;
    int n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    return n;
}
