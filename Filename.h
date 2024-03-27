#pragma once

#include <string>
#include <ostream>

using std::string;
using std::ostream;

enum extension_type : char {
    C, CC, CPP
};

struct Filename {
    string root;
    extension_type type;
};

inline ostream& operator<<(ostream& os, const Filename& fn) {
    os << fn.root;
    return os;
}