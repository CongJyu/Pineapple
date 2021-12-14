//
//  commands.hpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/13.
//

#ifndef commands_hpp
#define commands_hpp

#include <iostream>
#include <cstring>
#include <string>

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

void commands(string);

#endif /* commands_hpp */
