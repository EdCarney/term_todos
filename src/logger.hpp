#include <string>

namespace logger {

    enum log_level {
        TRACE,
        DEBUG,
        INFO,
        ERROR,
        PANIC
    };

    class logger {
        public:
            logger(char *log_file, bool verbose);
            ~logger();

            void log(std::string msg, log_level level = INFO);
    };
}
