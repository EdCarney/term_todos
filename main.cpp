#include <cstdio>
#include <sqlite3.h>
#include "src/logger.hpp"
#include "src/db_handler.hpp"

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

    printf("Done!\n");

    return 0;
}
