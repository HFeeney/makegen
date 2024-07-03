#include <filesystem>
#include <iostream>

#include <boost/process.hpp>

#include "Crawler.h"

#define C_PREPROCESSOR "cpp"
#define C_PREPROCESSOR_ARGS "-MM"
#define GREP_SEARCHER "grep"
#define GREP_SEARCHER_ARGS "-cE"
#define MAIN_REGEX "int +main *\\(.*\\)"

using namespace std;
using namespace filesystem;
namespace bp = boost::process;

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
		std::string::size_type nameLen = relPath.length() - nameStart - suffixLen - 1;
		internalName.root = relPath.substr(nameStart, nameLen);

		// build make rule
		bp::ipstream cppOutput;
		bp::child cpp(bp::search_path(C_PREPROCESSOR), C_PREPROCESSOR_ARGS, relPath, bp::std_out > cppOutput);
		string line;
		string subline;
		while (true) {
			getline(cppOutput, subline);
			if (subline.back() == '\\') {
				// remove ' \' from line
				subline = subline.substr(0, subline.length() - 2);
				line.append(subline);
			}
			else {
				line.append(subline);
				break;
			}
		}
		
		
		cpp.wait();
		makefile.prod_rules.push_back(line);

		// check is main
		int res = bp::system(bp::search_path(GREP_SEARCHER), GREP_SEARCHER_ARGS, MAIN_REGEX, relPath, bp::std_out > bp::null);
		if (!res) {
			makefile.mains.push_back(internalName);
		} else {
			makefile.non_mains.push_back(internalName);
		}
	}
}
