#include "Reader.h"
#include <cstdio>
#include <filesystem>
#include <fstream>

using std::string;

void read_makefile(Makefile& m) {
    // Check if an existing Makefile's flags can be imported.
    if (std::filesystem::exists("Makefile")) {
        // A file exists. Open the file.
        std::ifstream file;
        file.open("Makefile");

        string line;
        // Loop through lines of the file
        while (std::getline(file, line)) {
            // If the line contains a colon, assume a rule has been
            // encountered and exit the file.
            if (line.find(':') != string::npos) {
                break;
            }

            // Skip lines that are not assignments.
            size_t index_equals;
            if ((index_equals = line.find('=')) == string::npos) {
                continue;
            }

            string left_side = line.substr(0, index_equals);
            string right_side = line.substr(index_equals + 1, string::npos);

            // Match the variable name left of the assignment to the field that
            // should be initialized with the rest of the line.
            if (left_side == "CC") {
                m.cc = right_side;
            } else if (left_side == "GCC") {
                m.gcc = right_side;
            } else if (left_side == "BFLAGS") {
                m.bflags = right_side;
            } else if (left_side == "CFLAGS") {
                m.cflags = right_side;
            } else if (left_side == "DFLAGS") {
                m.dflags = right_side;
            } else if (left_side == "LFLAGS") {
                m.lflags = right_side;
            } else if (left_side == "LIBS") {
                m.libs = right_side;
            }
        }

        
    }
}
