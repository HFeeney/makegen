#pragma once

#include "MakefileStruct.h"


// Initializes the flags of the passed makefile struct with those found in the
// makefile in the working directory if it exists. Flags may be overridden if
// new values are found in the existing makefile. The flags must be present at
// the top of the makefile and before any rules.
//    m - the makefile struct to be initialized
void read_makefile(Makefile& m);