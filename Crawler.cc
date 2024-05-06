#include <filesystem>
#include <iostream>

#include "Crawler.h"

using namespace std;
using namespace filesystem;

void crawl_files(Makefile& makefile) {
	// loop through files
	for (const directory_entry& file : recursive_directory_iterator(".", directory_options::skip_permission_denied)) {
		// build file internal name struct
		if (!file.is_regular_file()) continue;
		string relPath(file.path().string());
		Filename internalName;
		std::string::size_type suffixLen;
		if (relPath.ends_with(".c")) {
			internalName.type = C;
			suffixLen = 1;
		} else if (relPath.ends_with(".cc")) {
			internalName.type = CC;
			suffixLen = 2;
		} else if (relPath.ends_with(".cpp")) {
			internalName.type = CPP;
			suffixLen = 3;
		} else continue;
		std::string::size_type nameStart = relPath.find_last_of(path::preferred_separator) + 1;
		std::string::size_type nameLen = relPath.length() - nameStart - suffixLen;
		internalName.root = relPath.substr(nameStart, nameLen);

		// build make rule

		// check is main
	}
}