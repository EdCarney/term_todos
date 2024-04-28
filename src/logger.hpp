#ifndef LOGGER_HPP_DEFINED
#define LOGGER_HPP_DEFINED

#include <fstream>
#include <string>

static std::string log_level_text_map[] = { "TRACE", "DEBUG", "INFO", "ERROR", "PANIC" };

namespace logger {

    enum log_level {
        TRACE,
        DEBUG,
        INFO,
        ERROR,
        PANIC
    };

    static const std::string get_log_level_text(log_level level);

    class logger {
        public:
            logger(const char *log_file, bool console_log = false);
            ~logger();

            void log(const std::string msg, log_level level = INFO);

        private:
            bool _console_log;
            std::ofstream _log_file;
            void _print_to_streams(const std::string msg);
    };
}

#endif // LOGGER_HPP_DEFINED
