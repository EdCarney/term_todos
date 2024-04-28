#include <iostream>
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
    todo t = handler->get_todo(0);

    std::cout << "id: " << t.id << "todo: " << t.text << std::endl;

    return 0;
}
