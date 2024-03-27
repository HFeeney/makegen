#include <iostream>
#include <fstream>
#include <string>

#include "Writer.h"
#include "io_error.h"

using std::ofstream;
using std::ios;
using std::endl;

inline bool requiresGCC(Filename& fn) {
    return fn.type != C;
}

bool requiresGCC(string& rule) {
    const char* str = rule.c_str();
    while (*str) {
        if (*str == '.') {
            if (*(str + 1) == 'c') {
                if ((*(str + 2) == 'c' && *(str + 3) == ' ') || (*(str + 2) == 'p' && *(str + 3) == 'p') && *(str + 4) == ' ') {
                    return true;
                }
            }
        }
        str++;
    }
    return false;
}

void write_makefile(Makefile& MFstruct) {
    // open file
    ofstream MFfile("Makefile", ios::out | ios::trunc);
    if (!MFfile.is_open()) {
        throw new io_error("Failed to open Makefile for writing");
    }

    // print variables
    MFfile << "CC=" << MFstruct.cc << endl;
    MFfile << "GCC=" << MFstruct.gcc << endl;
    MFfile << "CFLAGS=" << MFstruct.cflags << endl;
    MFfile << "DFLAGS=" << MFstruct.dflags << endl;
    MFfile << "BFLAGS=" << MFstruct.bflags << endl;
    MFfile << "LFLAGS=" << MFstruct.lflags << endl;
    MFfile << "LIBS=" << MFstruct.libs << endl << endl;

    // print default rules
    MFfile << "debug: override CFLAGS+=$(DFLAGS)" << endl;
    MFfile << "debug: all" << endl << endl;
    MFfile << "build: override CFLAGS+=$(BFLAGS)" << endl;
    MFfile << "build: all" << endl << endl;
    MFfile << "all:";
    for (auto& pr : MFstruct.mains) {
        MFfile << " " << pr.root;
    }
    MFfile << endl << endl;
    
    // check CC/GCC usage
    bool nonMainsRequireGCC = false;
    for (auto& nm : MFstruct.non_mains) {
        if (requiresGCC(nm)) {
            nonMainsRequireGCC = true;
            break;
        }
    }

    // print linking rules
    for (auto& main : MFstruct.mains) {
        MFfile << main << ": " << main << ".o";
        for (auto& nonmain : MFstruct.non_mains) {
            MFfile << " " << nonmain << ".o";
        }
        MFfile << endl;
        MFfile << "\t$(";
        if (nonMainsRequireGCC || requiresGCC(main)) MFfile << "G";
        MFfile << "CC) $(LFLAGS) -o $@ $^ $(LIBS)" << endl << endl;
    }

    // print compilation rules
    for (string& rule : MFstruct.prod_rules) {
        MFfile << rule << endl;
        MFfile << "\t$(";
        if (requiresGCC(rule)) MFfile << "G";
        MFfile << "CC) $(CFLAGS) -c -o $@ $<" << endl << endl;
    }

    MFfile << "clean:" << endl;
    MFfile << "\t/bin/rm -f makegen *.o" << endl;
    MFfile.close();
}