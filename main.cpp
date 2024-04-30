#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <filesystem>
#include <sqlite3.h>
#include "src/logger.hpp"
#include "src/db_handler.hpp"

using db_interface::todo;

void print_all_todos(db_interface::db_handler *handler) {
    std::vector<todo> todos = handler->get_todos();
    for (auto &t : todos) {
        std::cout << "id: " << t.id << ", todo: " << t.text << std::endl;
    }
}

bool check_cmd_arg(char *cmd, std::vector<std::string> valid_cmds) {
    for (auto &valid_cmd : valid_cmds) {
        if (std::strcmp(cmd, valid_cmd.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

void add_todo(db_interface::db_handler *handler, char *text) {
    handler->add_todo((std::string)text);
}

void delete_todo(db_interface::db_handler *handler, char *id) {
    handler->delete_todo(atoi(id));
}

void update_todo(db_interface::db_handler *handler, char *id, char *text) {
    handler->update_todo({ atoi(id), (std::string)text });
}
void print_usage() {
    std::cout << "term-todos is a simple CLI todo tracker" << std::endl;
    std::cout << "\tls/list: lists todos" << std::endl;
    std::cout << "\ta[dd] TODO_TEXT: adds a new todo" << std::endl;
    std::cout << "\td[elete] TODO_ID: deletes a todo by id" << std::endl;
    std::cout << "\tu[pdate] TODO_ID TODO_TEXT: updates a todo with new text" << std::endl;
}

void print_invalid_cmd(char *cmd) {
    std::cout << "Invalid command: " << cmd << std::endl;
    print_usage();
}

int main(int argc, char* argv[]) {

    // read arg cmds
    //  s: strikethrough note

    const char *env_home;
    std::string log_file = "todos.log", db_file = "todos.db";
    if (!(env_home = std::getenv("HOME"))) {
        std::cout << "No $HOME env variable found, DB and log files will be local" << std::endl;
        env_home = ".";
    }
    std::string parent_folder = (std::string)env_home + "/.todos/";
    std::string log_path = parent_folder +  log_file;
    std::string db_path = parent_folder + db_file;

    std::filesystem::create_directory(parent_folder);

    logger::logger *lgr = new  logger::logger(log_path.c_str());
    db_interface::db_handler *handler = new db_interface::db_handler(db_path.c_str(), lgr);

    switch (argc) {
        case 1: {
            print_usage();
            break;
        }
        case 2: {
            char *cmd = argv[1];
            if (check_cmd_arg(cmd, { "ls", "list"})) {
                print_all_todos(handler);
            } else {
                print_invalid_cmd(cmd);
            }
            break;
        }
        case 3: {
            char *cmd = argv[1];
            char *cmd_arg = argv[2];
            if (check_cmd_arg(cmd, { "a", "add" })) {
                add_todo(handler, cmd_arg);
            } else if (check_cmd_arg(cmd, { "d", "delete" })) {
                delete_todo(handler, cmd_arg);
            } else {
                print_invalid_cmd(cmd);
            }
            break;
        }
        case 4: {
            char* cmd = argv[1];
            char* cmd_arg_1 = argv[2];
            char* cmd_arg_2 = argv[3];
            if (check_cmd_arg(cmd, { "u", "update" })) {
                update_todo(handler, cmd_arg_1, cmd_arg_2);
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
