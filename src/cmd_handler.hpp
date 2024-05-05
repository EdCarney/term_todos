#ifndef CMD_HANDLER_HPP_DEFINED
#define CMD_HANDLER_HPP_DEFINED

#include "db_handler.hpp"
#include <string>
#include <vector>

namespace cmd_interface {

    typedef std::vector<std::vector<std::string>> cmd_sequences;
    typedef std::vector<void (*)(std::vector<std::string>)> cmd_functions;

    struct cmd_def {
        int num_args;
        cmd_sequences sequences;
        cmd_functions functions;
    };

    class cmd_handler {
        public:
            cmd_handler(std::string log_file_path, std::string db_file_path);
            void handle_cmd(int argc, char *argv[]);

        private:
            static db_interface::db_handler *_handler;
            static std::vector<cmd_def> _cmd_defs;

            static void _print_all_todos(std::vector<std::string> args);
            static void _add_todo(std::vector<std::string> args);
            static void _delete_todo(std::vector<std::string> args);
            static void _update_todo_text(std::vector<std::string> args);
            static void _toggle_todo_checked(std::vector<std::string> args);
            static void _print_invalid_cmd(std::vector<std::string> args);
            static void _print_usage(std::vector<std::string> args);
    };
}

#endif // CMD_HANDLER_HPP_DEFINED
