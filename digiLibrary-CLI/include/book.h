//  book.h
//
//  commands, and operations about library
//  2021-12-31 Rain Chen

#ifndef BOOK_H_
#define BOOK_H_

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <filesystem>
#include <unistd.h>

using namespace std;

class Book {
public:
    Book();
    ~Book();
    void help();
    void quit();
    void version();
    void lsbook(string);
    void search(string);
    void stype(string);
    void addbook(string);
    void delbook(string);
    void lsborrow(string);
    void lsmybook(string, string);
    void borrow(string, string);
    void returnbook(string, string);
    void import(string);
private:
    string name;
    string isbn;
    string author;
    string type;
    long long num;
    string bookline;
};

#endif
