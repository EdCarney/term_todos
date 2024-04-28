#include "logger.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace logger {

    static const std::string get_log_level_text(log_level level) {
        return log_level_text_map[level];
    }

    logger::logger(const char *log_file, bool console_log) {
        _log_file.open(log_file);
        _console_log = console_log;
    }

    logger::~logger() {
        _log_file.close();
    }

    void logger::log(std::string msg, log_level level) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_now = std::chrono::system_clock::to_time_t(now);
        
        _log_file << std::put_time(std::localtime(&t_now), "%F-%T")
                  << " (" << get_log_level_text(level) << ") : "
                  << msg << std::endl;

        if (_console_log) {
            std::cout << std::put_time(std::localtime(&t_now), "%F-%T")
                      << " (" << get_log_level_text(level) << ") : "
                      << msg << std::endl;
        }
    }
}
