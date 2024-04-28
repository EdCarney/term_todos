#include <cstdio>
#include <sqlite3.h>

int main(int argc, char* argv[]) {

    // read arg cmds
    //  a: add note
    //  u: update note
    //  d: delete note
    //  s: strikethrough note

    sqlite3 *db;
    int return_code;

    return_code = sqlite3_open("test.db", &db);

    if (return_code) {
        printf("Error opening DB file\n");
    }

    sqlite3_stmt *stmt;
    const char *sql_cmd = "create table todos (id int);\0";
    return_code = sqlite3_prepare_v2(db, sql_cmd, -1, &stmt, nullptr);

    if (return_code) {
        printf("Error preparing SQL statement\n");
    }

    return_code = sqlite3_step(stmt);

    if (return_code != SQLITE_DONE) {
        printf("Error creating table\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    printf("Done!\n");

    return 0;
}
