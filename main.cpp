#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "src/logger.hpp"
#include "src/db_handler.hpp"

using db_interface::todo;

int main(int argc, char* argv[]) {

    // read arg cmds
    //  a: add note
    //  u: update note
    //  d: delete note
    //  s: strikethrough note
    //  ls: list notes

    sqlite3 *db;
    int return_code;
    logger::logger *lgr = new  logger::logger("test.log", true);

    db_interface::db_handler *handler = new db_interface::db_handler("test.db", lgr);
    todo t1 = handler->get_todo(2);

    handler->add_todo("some new stuff to do");

    std::vector<todo> todos = handler->get_todos();

    for (auto &t : todos) {
        std::cout << "id: " << t.id << ", todo: " << t.text << std::endl;
    }
    /*
    handler->delete_todo(4);
    handler->update_todo(todo { 5, "another set of things to do" });
    */


    return 0;
}
