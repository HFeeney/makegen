#pragma once

#include <vector>
#include <string>

using std::vector;
using std::string;

struct Makefile {
    string cc;  // C compiler variable
    string gcc;  // C++ compiler variable
    string cflags;  // compilation flags variables
    string bflags;  // build product flags variable
    string dflags;  // debugging product flags variable
    string lflags;  // linker flags variable
    string libs;  // linker appending libraries variable

    vector<string> mains;  // roots of files with main functions
    vector<string> non_mains;  // roots of files without main functions
    vector<string> prod_rules;  // rules for compiling objects
};