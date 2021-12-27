//
//  commands.hpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/13.
//

#ifndef commands_hpp
#define commands_hpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
#include <filesystem>
#include <unistd.h>
using namespace std;
//  the digiLibrary structure -- store info of books
struct digiLibrary {
    string bname;
    string isbn;
    string author;
    string location;
    bool borrow;
};
//  the normal user profiles -- store username and passwords
struct nusProfile {
    string nusername;
    string npassword;
};
//  commands
void commands(string, string);

#endif /* commands_hpp */
