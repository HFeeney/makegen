#include "Makefile.h"

// writes the gven makefile struct to a file
// Throws io_error* on failure, client is responsible for deleting exception
void write_makefile(Makefile&);