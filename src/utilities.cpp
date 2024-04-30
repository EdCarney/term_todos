#include "utilities.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace utilities {

    std::string get_app_file_path(std::string file_name) {

        const char *env_home;
        if (!(env_home = std::getenv("HOME"))) {
            env_home = ".";
        }
        std::string parent_folder = (std::string)env_home + "/.todos/";
        std::string full_path = parent_folder +  file_name;

        std::filesystem::create_directory(parent_folder);

        return full_path;
    }

    bool string_in_set(const char *val, std::vector<std::string> valid_vals) {
        for (auto &valid_val : valid_vals) {
            if (std::strcmp(val, valid_val.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }
}
