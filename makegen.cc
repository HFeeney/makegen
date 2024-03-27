#include <iostream>
#include <cstdlib>
#include <stdexcept>

#include "Reader.h"
#include "Crawler.h"
#include "Writer.h"

using std::cout;
using std::endl;
using std::runtime_error;

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
    try {
        Makefile m;
        if (argc != 1) {
            if (!(argc == 2 && argv[2][0] == '-' && argv[2][1] == 'n' && argv[2][2] == '\0')) {
                // invalid
                cout << "Usage: " << argv[0] << endl;
                return EXIT_FAILURE;
            }
            // force new
        } else {
            // try read
            m = read_makefile();
        }

        // crawl
        crawl_files(m);
        // write
        write_makefile(m);
    } catch (runtime_error* re) {
        cout << re->what() << endl;
        delete re;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
