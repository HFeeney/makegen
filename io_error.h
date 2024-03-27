#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

class io_error : public runtime_error {
 public:
    io_error(const string& what) : runtime_error(what) { }
    io_error(const char* what) : runtime_error(what) { }
};
