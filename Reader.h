#pragma once

#include "MakefileStruct.h"

// reads the current directory for a makefile
// fills the returned struct in with contents of makefile flags
// returns a default makefile struct if Makefile not found
Makefile read_makefile();