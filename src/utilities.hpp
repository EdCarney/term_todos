#ifndef UTILITIES_HPP_DEFINED
#define UTILITIES_HPP_DEFINED

#include <string>
#include <vector>

namespace utilities {

    // returns full app path to a file with the provided filename
    // generates necessary home directories to ensure path is valid
    std::string get_app_file_path(std::string file_name);

    // validates if the provided val is the set of valid vals
    bool string_in_set(std::string, std::vector<std::string> valid_vals);
}

#endif // UTILITIES_HPP_DEFINED
