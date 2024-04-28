#include <iostream>
#include <vector>
#include <cstring>
#include <sqlite3.h>
#include "src/logger.hpp"
#include "src/db_handler.hpp"

using db_interface::todo;

void print_all(db_interface::db_handler *handler) {
    std::vector<todo> todos = handler->get_todos();
    for (auto &t : todos) {
        std::cout << "id: " << t.id << ", todo: " << t.text << std::endl;
    }
}

void print_usage() {
}

void print_invalid_cmd(char *cmd) {
    std::cout << "Invalid command: " << cmd << std::endl;
    print_usage();
}

bool check_cmd_arg(char *cmd, std::vector<std::string> valid_cmds) {
    for (auto &valid_cmd : valid_cmds) {
        if (std::strcmp(cmd, valid_cmd.c_str()) == 0) {
            return true;
        }
    }
    return false;
}

void add_todo(db_interface::db_handler *handler, char *cmd_arg) {
}

void delete_todo(db_interface::db_handler *handler, char *cmd_arg) {
}

int main(int argc, char* argv[]) {

    // read arg cmds
    //  a: add note
    //  u: update note
    //  d: delete note
    //  s: strikethrough note
    //  ls: list notes
    //

    logger::logger *lgr = new  logger::logger("test.log");
    db_interface::db_handler *handler = new db_interface::db_handler("test.db", lgr);

    switch (argc) {
        case 1: {
            // print usage
            break;
        }
        case 2: {
            char *cmd = argv[1];
            if (check_cmd_arg(cmd, { "ls", "list"})) {
                print_all(handler);
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
            // update
            break;
        }
        default: {
            // invalid
            break;
        }
    }

    return 0;
}
