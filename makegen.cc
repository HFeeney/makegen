

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

int main(int argc, char** argv){

  // Create a Makefile struct, and initialize its fields.
  
  // Iterate through all files in the current directory.
    // If the current file's extension is not one of .c, .cc, or .cpp, skip it

    // Get the production rule for this file, and add it to the struct.

    // Strip off the file's extension to get the root.

    // Check if the current file contains a main function
      // It does, add the root to the mains field of the struct.

      // It doesn't, add the root to the non_mains field of the struct.

  return 0;
}
