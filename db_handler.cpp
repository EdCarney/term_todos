#include "db_handler.hpp"
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdio>

namespace db_interface {

    db_handler::db_handler(const char *db_file) {
        handle_ret_code(sqlite3_open(db_file, &db));
        initialize_db();
    }

    db_handler::~db_handler() {
        handle_ret_code(sqlite3_close(db));
    }

    std::vector<todo>

    int db_handler::add_todo(std::string todo_text) {
        return 0;
    }

    int db_handler::delete_todo(std::string todo_text) {
        return 0;
    }

    void db_handler::initialize_db() {
        sqlite3_stmt *stmt;
        const char *cmd = "CREATE TABLE IF NOT EXISTS todos (id INT PRIMARY KEY, todo TEXT);\0";
        handle_ret_code(sqlite3_prepare_v2(db, cmd, -1, &stmt, nullptr));
        sqlite3_finalize(stmt);
    }
}
