#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <cstring>

#include "Reader.h"
#include "Crawler.h"
#include "Writer.h"
#include "MakefileStruct.h"

using std::cout;
using std::endl;
using std::runtime_error;

/**
 * Returns true if the two cstrings are equal (identical)
*/
inline bool streq(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs) == 0;
}

// Initialize the makefile struct
    // Check if a makefile exists already
        // It doesn't, initialize flags to default values and vectors to empty.
        // It does, parse the flags that exist in the makefile struct (assume
        // they are there)
            // Loop through lines of the file
                // If the line contains a colon, assume a rule has been
                // encountered and exit the file.
                // Otherwise, match the variable name left of the assignment
                // to the field that should be initialized with the rest of the
                // line.

int main(int argc, char** argv) {
    // parse options
    bool forceNew = false;
    for (int i = 1; i < argc; i++) {
        char* arg = argv[i];
        if (streq(arg, "-n") || streq(arg, "--new")) {
            forceNew = true;
            continue;
        }
        char* field = strchr(arg, '=');
        if (field != nullptr) {
            *field = '\0';
            field++;
            if (streq(arg, "--CC")) {
                default_cc = field;
                continue;
            }
            if (streq(arg, "--GCC")) {
                default_gcc = field;
                continue;
            }
            if (streq(arg, "--CFLAGS")) {
                default_cflags = field;
                continue;
            }
            if (streq(arg, "--BFLAGS")) {
                default_bflags = field;
                continue;
            }
            if (streq(arg, "--DFLAGS")) {
                default_dflags = field;
                continue;
            }
            if (streq(arg, "--LFLAGS")) {
                default_lflags = field;
                continue;
            }
            if (streq(arg, "--LIBS")) {
                default_libs = field;
                continue;
            }
        }
        
        // invalid argument
        cout << "Unparseable argument: " << arg << endl;
        cout << "Usage: " << argv[0] << " [-n] [--<field name>=<default value>]" << endl;
        return EXIT_FAILURE;
    }

    try {
        // read
        Makefile m;
        if (!forceNew) m = read_makefile();
        // crawl
        crawl_files(m);
        // write
        write_makefile(m);
    } catch (runtime_error* re) {
        cout << re->what();
        delete re;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
