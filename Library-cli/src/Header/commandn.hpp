//
//  commandn.hpp
//  Library-cli
//
//  Created by Rain Chen on 2021/12/14.
//

#ifndef commandn_hpp
#define commandn_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

//  the digiLibrary structure -- store info of books
struct nudigiLibrary {
    string bname;
    string isbn;
    string author;
    string location;
    bool borrow;
};

//  user profiles
struct nuserprof {
    string nusername;
    string npassword;
};

void commandn(string, string);

#endif /* commandn_hpp */
