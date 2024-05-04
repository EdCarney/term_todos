#include "src/utilities.hpp"
#include "src/logger.hpp"
#include "src/db_handler.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <sqlite3.h>

using db_interface::todo;

void print_all_todos(db_interface::db_handler *handler) {
    std::vector<todo> todos = handler->get_todos();
    for (auto &t : todos) {
        std::string check_mark = t.checked ? "X" : " ";
        std::cout << t.id << ": [" << check_mark << "] " << t.text << std::endl;
    }
}
void add_todo(db_interface::db_handler *handler, char *text) {
    handler->add_todo((std::string)text);
}

void delete_todo(db_interface::db_handler *handler, char *id) {
    handler->delete_todo(atoi(id));
}

void update_todo_text(db_interface::db_handler *handler, char *id, char *text) {
    handler->update_todo_text(std::atoi(id), std::string(text));
}

void toggle_todo_checked(db_interface::db_handler *handler, char *id) {
    handler->toggle_todo_checked(std::atoi(id));
}

void print_usage() {
    std::cout << "term-todos is a simple CLI todo tracker" << std::endl;
    std::cout << "\tls/list: lists todos" << std::endl;
    std::cout << "\ta[dd] TODO_TEXT: adds a new todo" << std::endl;
    std::cout << "\tc[heck] TODO_ID: checks off todo by id" << std::endl;
    std::cout << "\td[elete] TODO_ID: deletes a todo by id" << std::endl;
    std::cout << "\tu[pdate] TODO_ID TODO_TEXT: updates a todo with new text" << std::endl;
}

void print_invalid_cmd(char *cmd) {
    std::cout << "Invalid command: " << cmd << std::endl;
    print_usage();
}

int main(int argc, char* argv[]) {

    logger::logger *lgr = new  logger::logger(utilities::get_app_file_path("todos.log").c_str());
    db_interface::db_handler *handler = new db_interface::db_handler(utilities::get_app_file_path("todos.db").c_str(), lgr);

    switch (argc) {
        case 1: {
            print_usage();
            break;
        }
        case 2: {
            char *cmd = argv[1];
            if (utilities::string_in_set(cmd, { "ls", "list"})) {
                print_all_todos(handler);
            } else {
                print_invalid_cmd(cmd);
            }
            break;
        }
        case 3: {
            char *cmd = argv[1];
            char *cmd_arg = argv[2];
            if (utilities::string_in_set(cmd, { "a", "add" })) {
                add_todo(handler, cmd_arg);
            } else if (utilities::string_in_set(cmd, { "d", "delete" })) {
                delete_todo(handler, cmd_arg);
            } else if (utilities::string_in_set(cmd, { "c", "check" })) {
                toggle_todo_checked(handler, cmd_arg);
            } else {
                print_invalid_cmd(cmd);
            }
            break;
        }
        case 4: {
            char* cmd = argv[1];
            char* cmd_arg_1 = argv[2];
            char* cmd_arg_2 = argv[3];
            if (utilities::string_in_set(cmd, { "u", "update" })) {
                update_todo_text(handler, cmd_arg_1, cmd_arg_2);
            } else {
                print_invalid_cmd(cmd);
            }
            break;
        }
        default: {
            print_usage();
            break;
        }
    }

    return 0;
}
