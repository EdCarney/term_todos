#include "cmd_handler.hpp"
#include "db_handler.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace cmd_interface {

    db_interface::db_handler *cmd_handler::_handler;

    cmd_handler::cmd_handler(std::string log_file_path, std::string db_file_path) {
        logger::logger *lgr = new logger::logger(log_file_path.c_str());
        _handler = new db_interface::db_handler(db_file_path.c_str(), lgr);
    }

    void cmd_handler::_print_usage(std::vector<std::string> args) {
        std::cout << "term-todos is a simple CLI todo tracker" << std::endl;
        std::cout << "\tls/list\t\t\t\tlists todos" << std::endl;
        std::cout << "\ta[dd] TODO_TEXT\t\t\tadds a new todo" << std::endl;
        std::cout << "\tc[heck] TODO_ID\t\t\ttoggles check box for todo by id" << std::endl;
        std::cout << "\td[elete] TODO_ID\t\tdeletes a todo by id" << std::endl;
        std::cout << "\tu[pdate] TODO_ID TODO_TEXT\tupdates a todo with new text" << std::endl;
    }

    void cmd_handler::_print_all_todos(std::vector<std::string> args) {
        std::vector<db_interface::todo> todos = _handler->get_todos();
        for (auto &t : todos) {
            std::string check_mark = t.checked ? "X" : " ";
            std::cout << t.id << ": [" << check_mark << "] " << t.text << std::endl;
        }
    }

    void cmd_handler::_add_todo(std::vector<std::string> args) {
        std::string text = args.at(1);
        _handler->add_todo(text);
    }

    void cmd_handler::_delete_todo(std::vector<std::string> args) {
        for (int i = 1; i < args.size(); i++) {
            int id = std::atoi(args.at(i).c_str());
            _handler->delete_todo(id);
        }
    }

    void cmd_handler::_update_todo_text(std::vector<std::string> args) {
        int id = std::atoi(args.at(1).c_str());
        std::string text = args.at(2);
        _handler->update_todo_text(id, text);
    }

    void cmd_handler::_toggle_todo_checked(std::vector<std::string> args) {
        int id = std::atoi(args.at(1).c_str());
        _handler->toggle_todo_checked(id);
    }

    void cmd_handler::_print_invalid_cmd(std::vector<std::string> args) {
        std::cout << "Invalid command: " << args.at(0) << std::endl;
    }

    cmd_sequences arg_0_cmd_seqs = { };

    cmd_sequences arg_1_cmd_seqs = {
        { "l", "ls", "list" }
    };

    cmd_sequences arg_2_cmd_seqs = {
        { "a", "add" },
        { "c", "check" }
    };

    cmd_sequences arg_3_cmd_seqs = {
        { "u", "update" }
    };

    cmd_sequences arg_any_cmd_seqs = {
        { "d", "delete" },
    };

    std::vector<cmd_def> cmd_handler::_cmd_defs {
        { 0,  arg_0_cmd_seqs,   { _print_usage } },
        { 1,  arg_1_cmd_seqs,   { _print_all_todos } },
        { 2,  arg_2_cmd_seqs,   { _add_todo, _toggle_todo_checked } },
        { 3,  arg_3_cmd_seqs,   { _update_todo_text } },
        { -1, arg_any_cmd_seqs, { _delete_todo } },
    };

    void cmd_handler::handle_cmd(int argc, char *argv[]) {
        std::vector<std::string> args;

        // create new args w/out app name
        int i = 1;
        while (i < argc) {
            args.push_back(argv[i++]);
        }

        std::string arg = args.empty() ? "" : args.at(0);
        for (auto &def : _cmd_defs) {
            // find the cmd def with the correct # of args
            if (args.size() != def.num_args) {
                continue;
            }

            // try all the cmd seqs
            i = -1;
            while (++i < def.sequences.size()) {
                if (utilities::string_in_set(arg, def.sequences.at(i))) {
                    return def.functions.at(i)(args);
                }
            }
            
        }

        // handle cases with any arg count
        auto &def = _cmd_defs.back();
        i = -1;
        while (++i < def.sequences.size()) {
            if (utilities::string_in_set(arg, def.sequences.at(i))) {
                return def.functions.at(i)(args);
            }
        }
        
        // if none of the cmd seqs work then default to invalid cmd
        return _print_invalid_cmd(args);
    }
}
