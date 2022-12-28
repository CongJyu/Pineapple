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
    //  this is the boarder line
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    //  these help messages can be moved into a file to store
    //  TODO(Rain Chen): move these help tips to a file.
    cout << "Basic Commands:" << endl;
    cout << "    'version' -- show current version." << endl;
    cout << "    'help' -- get help." << endl;
    cout << "    'quit' -- quit digiLibrary." << endl;
    cout << "Account Settings:" << endl;
    cout << "    'passwd <New Username> <New Password>' -- change and set your password." << endl;
    cout << "    'lsuser' -- list all users." << endl;
    cout << "    'useradd' -- add a user." << endl;
    cout << "    'userdel <Username>' -- delete a user." << endl;
    cout << "    'resetpwd <Username>' -- reset someone's passwprd." << endl;
    cout << "Book Management:" << endl;
    cout << "    'lsbook' -- list all the books." << endl;
    cout << "    'addbook <Bookname> <ISBN/ISSN> <Author> <Type> <Number>' -- add a book to library." << endl;
    cout << "    'delbook <Bookname>' -- delete a book from library." << endl;
    cout << "    'search <Content>' -- search a book from library." << endl;
    cout << "    'stype <Type>' -- search type." << endl;
    cout << "    'borrow <ISBN/ISSN>' -- borrow a book from library." << endl;
    cout << "    'return <ISBN/ISSN>' -- return a book to library." << endl;
    cout << "    'lsmybook' -- list the books you've borrowed." << endl;
    cout << "    'lsborrow <Username>' -- see a user's borrowed books." << endl;
    cout << "    'import <New Book List> -- import a pile of books." << endl;
    cout << "Program Management:" << endl;
    cout << "    'clearlog' -- clear program log information." << endl;
    //  this is also a boarder line
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
    //  show the name of this program
    cout << "🍍 digiLibrary v1.5.0" << endl << endl;
    //  show the version of this program
    cout << "First Build Dec 2021. Current Build Jan 2022." << endl;
    //  show the author of this program
    cout << "By Rain Chen and Zheng ShuYao." << endl;
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    return;
}
//  quit
void Book::quit() {
    //  show goodbye message
    cout << "🍍 \033[36mGoodbye!\033[0m" << endl;
    //  return to main function and quit while-loop
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
    long long cnt = 0;
    while (getline(list, bookline)) {
        cout << bookline << endl;
        cnt++;
    }
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. All " << cnt << " book(s) listed.\033[0m" << endl;
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
    //  open book list file
    list.open(dir + "/books.txt");
    //  read and display book lists: a line each time
    long long cnt = 0;
    while (getline(list, bookline)) {
        if (bookline.find(content) != string::npos) {
            cout << bookline << endl;
            cnt++;
        }
    }
    //  close book library file
    list.close();
    for (int i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. " << cnt << " book(s) found.\033[0m" << endl;
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
    //  close book list file
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
    //  count the book list's lines
    ifstream countline;
    countline.open(dir + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    //  create a dynamic array
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
    for (long long i = 0; i < n; i++) {
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
    for (long long i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    for (long long i = 0; i < n; i++) {
        cout << bks[i].name << " "
        << bks[i].isbn << " "
        << bks[i].author << " "
        << bks[i].type << " "
        << bks[i].num;
        cout << endl;
    }
    for (long long i = 0; i < 80; i++) {
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
    for (long long i = 0; i < 80; i++) {
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
    for (long long i = 0; i < n; i++) {
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
    //  object "rtb" stands for "return books"
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
//  search for type
void Book::stype(string dir) {
    string target_type;
    cin >> target_type;
    cout << "Loading books..." << endl;
    //  count lines
    ifstream countline;
    countline.open(dir + "/books.txt", ios::in);
    string temp;
    long long n = 0;
    while (getline(countline, temp, '\n')) {
        n++;
    }
    countline.close();
    //  st stands for search type
    fstream st;
    st.open(dir + "/books.txt");
    Book * bks = new Book [n];
    long long j = 0;
    while (st.eof() != 1) {
        st >> bks[j].name
        >> bks[j].isbn
        >> bks[j].author
        >> bks[j].type
        >> bks[j].num;
        j++;
    }
    n = j - 1;
    for (long long i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    long long cnt = 0;
    for (long long i = 0; i < n; i++) {
        if (bks[i].type.find(target_type) != string::npos) {
            cout << bks[i].name << " "
            << bks[i].isbn << " "
            << bks[i].author << " "
            << bks[i].type << " "
            << bks[i].num << endl;
            cnt++;
        }
    }
    for (long long i = 0; i < 80; i++) {
        cout << "\033[36m-\033[0m";
    }
    cout << endl;
    cout << "🍍 \033[36mDone. All '" << target_type << "' type books listed. "
    << cnt << " book(s) in total.\033[0m" << endl;
    return;
}
//  import a pile of books
void Book::import(string dir) {
    //  enter the path of file
    string new_book_dir;
    cin >> new_book_dir;
    cout << "Ensure your data file path, for example, ";
    cout << "\"/Users/rainchen/Documents/newbooklist.txt\": ";
    cout << new_book_dir << endl;
    cout << "(Y/n): \033[35m";
    char sure;
    cin >> sure;
    cout << "\033[0m";
    if (sure == 'Y') {
        fstream imp;    //  import object
        //  countline
        ifstream countline;
        countline.open(new_book_dir, ios::in);
        string temp;
        long long n = 0;
        while (getline(countline, temp, '\n')) {
            n++;
        }
        countline.close();
        imp.open(new_book_dir);
        Book * bks = new Book [n];
        long long j = 0;
        while (imp.eof() != 1) {
            imp >> bks[j].name
            >> bks[j].isbn
            >> bks[j].author
            >> bks[j].type
            >> bks[j].num;
            j++;
        }
        n = j - 1;
        imp.close();
        imp.open(dir + "/books.txt", ios::app);
        for (long long i = 0; i < n; i++) {
            imp << bks[i].name << " "
            << bks[i].isbn << " "
            << bks[i].author << " "
            << bks[i].type << " "
            << bks[i].num << endl;
        }
        imp.close();
        cout << "🍍 \033[36mDone. Books imported.\033[0m" << endl;
    } else if (sure == 'n') {
        cout << "🍍 \033[36mOperation cancelled.\033[0m" << endl;
        return;
    } else {
        cout << "Failed." << endl;
        return;
    }
    return;
}
