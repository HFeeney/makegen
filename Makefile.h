#pragma once

#include <vector>
#include <string>

#include "Filename.h"

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

    vector<Filename> mains;  // roots of files with main functions
    vector<Filename> non_mains;  // roots of files without main functions
    vector<string> prod_rules;  // rules for compiling objects

    // default values for important variables
    Makefile() : 
        cc("gcc"),
        gcc("g++"),
        bflags("-O2"),
        dflags("-g -Og") { }
};