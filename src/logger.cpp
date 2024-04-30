#include "logger.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace logger {

    static const std::string get_log_level_text(log_level level) {
        return log_level_text_map[level];
    }

    std::string rpad(std::string str, int width, char pad) {
        int str_len = str.length();
        if (str_len >= width) {
            return str;
        }
        int num_pads = width - str_len;
        return str + std::string(num_pads, pad);
    }
    
    logger::logger(const char *log_file, bool console_log) {
        _log_file.open(log_file, std::ofstream::out | std::ofstream::app);
        _console_log = console_log;
        _print_header();
        log("Logger initialized.");
    }

    logger::~logger() {
        _log_file.close();
    }

    void logger::log(std::string msg, log_level level) {
        const auto now = std::chrono::system_clock::now();
        const std::time_t t_now = std::chrono::system_clock::to_time_t(now);
        std::string level_str = rpad("(" + get_log_level_text(level) + ")", 7, ' ');
        
        _log_file << std::put_time(std::localtime(&t_now), "%F-%T")
                  << " " << level_str << " : " << msg << std::endl;

        if (_console_log) {
            std::cout << std::put_time(std::localtime(&t_now), "%F-%T")
                  << " " << level_str << " : " << msg << std::endl;
        }
    }

    void logger::_print_header() {
        std::string header = std::string(40, '-');
        _log_file << header << std::endl;
    }

}
