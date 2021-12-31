//  book.cpp
//
//  compile with book.h
//  core process
//  2021-12-31 Rain Chen

#include "../include/book.h"
//  namespace
using namespace std;
//  default constructor
Book::Book() {}
//  default destructor
Book::~Book() {}
//  help command
void Book::help() {
    cout << "🍍 Welcome to digiLibrary. See the commands below:" << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "Basic commands:" << endl;
    cout << "    'version' -- show current version." << endl;
    cout << "    'help' -- get help." << endl;
    cout << "    'quit' -- quit digiLibrary." << endl;
    cout << "Account settings:" << endl;
    cout << "    'passwd <new username> <new password>' -- change and set your password." << endl;
    cout << "    'lsuser' -- list all users." << endl;
    cout << "    'useradd' -- add a user." << endl;
    cout << "    'userdel <Username>' -- delete a user." << endl;
    cout << "Book Management:" << endl;
    cout << "    'lsbook' -- list all the books." << endl;
    cout << "    'addbook <Bookname> <ISBN/ISSN> <Author> <Type> <Number>' -- add a book to library." << endl;
    cout << "    'delbook <Bookname>' -- delete a book from library." << endl;
    cout << "    'search <content>' -- search a book from library." << endl;
    cout << "    'borrow <ISBN/ISSN>' -- borrow a book from library." << endl;
    cout << "    'return <ISBN/ISSN>' -- return a book to library." << endl;
    cout << "    'lsmybook' -- list the books you've borrowed." << endl;
    cout << "    'lsborrow <Username>' -- see a user's borrowed books." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    return;
}
//  show version
void Book::version() {
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 digiLibrary v1.4.0" << endl;
    cout << "Build Dec 2021." << endl;
    cout << "Made by Rain Chen and Zheng ShuYao." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    return;
}
//  quir
void Book::quit() {
    cout << "🍍 \033[36mGoodbye!\033[0m" << endl;
    return;
}
//  list all books
void Book::lsbook(string dir) {
    cout << "Loading..." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    fstream list;
    list.open(dir + "/books.txt");
    while (getline(list, bookline)) {
        cout << bookline << endl;
    }
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. All books listed.\033[0m" << endl;
    return;
}
//  search books
void Book::search(string dir) {
    string content;
    cin >> content;
    cout << "Loading..." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    fstream list;
    list.open(dir + "/books.txt");
    while (getline(list, bookline)) {
        if (bookline.find(content) != string::npos) {
            cout << bookline << endl;
        }
    }
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. Books listed.\033[0m" << endl;
    return;
}
//  add a book
void Book::addbook(string dir) {
    string newbookname, newbookisbn, newbookauthor;
    string newbooktype, newbooknumber;
    cin >> newbookname
    >> newbookisbn
    >> newbookauthor
    >> newbooktype
    >> newbooknumber;
    fstream add;
    //  open book list
    add.open(dir + "/books.txt", ios::app);
    add << newbookname << " "
    << newbookisbn << " "
    << newbookauthor << " "
    << newbooktype << " "
    << newbooknumber << endl;
    add.close();
    cout << "🍍 " << "\033[36mDone. The book '" << newbookname << "' is added.\033[0m" << endl;
    return;
}
//  delete a book
void Book::delbook(string dir) {
    string targetbook;
    cin >> targetbook;
    fstream del;
    del.open(dir + "/books.txt");
    ifstream countline;
    countline.open(dir + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    Book * bks = new Book [n];
    long long j = 0;
    while (del.eof() != 1) {
        del >> bks[j].name
        >> bks[j].isbn
        >> bks[j].author
        >> bks[j].type
        >> bks[j].num;
        j++;
    }
    n = j - 1;
    del.close();
    del.open(dir + "/books.txt", ios::out|ios::trunc);
    for (int i = 0; i < n; i++) {
        if (bks[i].name == targetbook) {
            continue;
        }
        del << bks[i].name << " "
        << bks[i].isbn << " "
        << bks[i].author << " "
        << bks[i].type << " "
        << bks[i].num;
        del << endl;
    }
    del.close();
    delete [] bks;
    cout << "🍍 \033[36mDone! '" << targetbook << "' is deleted.\033[0m" << endl;
    return;
}
//  list borrow books
void Book::lsborrow(string dir) {
    string targetuser;
    cin >> targetuser;
    cout << "Loading books..." << endl;
    fstream borrow;
    borrow.open(dir + "/" + targetuser + ".digidata");
    ifstream countline;
    countline.open(dir + targetuser + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    Book * bks = new Book [n];
    long long j = 0;
    while (borrow.eof() != 1) {
        borrow >> bks[j].name
        >> bks[j].isbn
        >> bks[j].author
        >> bks[j].type
        >> bks[j].num;
        j++;
    }
    n = j - 1;
    borrow.close();
    cout << "Current books '" << targetuser << "'ve borrowed:" << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << bks[i].name << " "
        << bks[i].isbn << " "
        << bks[i].author << " "
        << bks[i].type << " "
        << bks[i].num;
        cout << endl;
    }
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    delete [] bks;
    cout << "🍍 \033[36mDone. All '" << targetuser << "''s books are listed.\033[0m" << endl;
    return;
}
//  list my books
void Book::lsmybook(string dir, string username) {
    cout << "Loading..." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    fstream list;
    list.open(dir + "/" + username + ".digidata");
    while (getline(list, bookline)) {
        cout << bookline << endl;
    }
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. All books listed.\033[0m" << endl;
    return;
}
//  borrow books from library
void Book::borrow(string dir, string username) {
    string borrowbook;
    cin >> borrowbook;
    fstream bor;
    //  countline
    ifstream countline;
    countline.open(dir + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    bor.open(dir + "/books.txt");
    Book * bks = new Book [n];
    long long j = 0;
    while (bor.eof() != 1) {
        bor >> bks[j].name
        >> bks[j].isbn
        >> bks[j].author
        >> bks[j].type
        >> bks[j].num;
        j++;
    }
    n = j - 1;
    bor.close();
    string userpath = dir + "/" + username + ".digidata";
    bor.open(userpath, ios_base::app);
    for (int i = 0; i < n; i++) {
        if (bks[i].isbn == borrowbook) {
            bor << bks[i].name << " "
            << bks[i].isbn << " "
            << bks[i].author << " "
            << bks[i].type << " "
            << bks[i].num << endl;
            break;
        }
    }
    delete [] bks;
    bor.close();
    cout << "🍍 \033[36mDone. Borrow '" << borrowbook << "' from library.\033[0m" << endl;
    return;
}
//  return a book to library
void Book::returnbook(string dir, string username) {
    string returnb;
    cin >> returnb;
    fstream rtb;
    string userpath = dir + "/" + username + ".digidata";
    rtb.open(userpath);
    //  countline
    ifstream countline;
    countline.open(dir + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    Book * bks = new Book [n];
    long long j = 0;
    while (rtb.eof() != 1) {
        rtb >> bks[j].name
        >> bks[j].isbn
        >> bks[j].author
        >> bks[j].type
        >> bks[j].num;
        j++;
    }
    n = j - 1;
    rtb.close();
    rtb.open(userpath, ios::out|ios::trunc);
    for (long long i = 0; i < n; i++) {
        if (bks[i].isbn == returnb) {
            continue;
        } else {
            rtb << bks[i].name << " "
            << bks[i].isbn << " "
            << bks[i].author << " "
            << bks[i].type << " "
            << bks[i].num << endl;
        }
    }
    rtb.close();
    cout << "🍍 \033[36mDone. Return '" << returnb << "' to library.\033[0m" << endl;
    return;
}

