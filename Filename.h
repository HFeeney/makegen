#include <string>

using std::string;

enum extension_type : char {
    C, CC, CPP
};

struct Filename {
    string root;
    extension_type type;
};