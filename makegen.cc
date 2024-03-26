



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
