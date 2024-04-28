#include "db_handler.hpp"
#include <sqlite3.h>
#include <vector>
#include <string>
#include <cstdio>

namespace db_interface {

    db_handler::db_handler(const char *db_file) {
        int ret_code = sqlite3_open_v2(db_file, &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        initialize_db();
    }

    db_handler::~db_handler() {
        handle_ret_code(sqlite3_close(_db));
    }

    std::vector<todo> db_handler::get_todos() {
        return std::vector<todo>(0);
    }

    todo db_handler::get_todo(int id) {
        return todo {};
    }

    int db_handler::add_todo(std::string todo_text) {
        return 0;
    }

    int db_handler::update_todo(todo new_todo) {
        return 0;
    }

    int db_handler::delete_todo(int id) {
        return 0;
    }

    int db_handler::strikethrough_todo(int id) {
        return 0;
    }

    void db_handler::initialize_db() {
        sqlite3_stmt *stmt;
        const char *cmd = "CREATE TABLE IF NOT EXISTS todos (id INT PRIMARY KEY, todo TEXT);\0";
        handle_ret_code(sqlite3_prepare_v2(_db, cmd, -1, &stmt, nullptr));
        sqlite3_finalize(stmt);
    }

    void db_handler::handle_ret_code(int ret_code) {
    }
}
