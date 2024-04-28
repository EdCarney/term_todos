#include "db_handler.hpp"
#include <sqlite3.h>
#include <vector>
#include <string>

using std::string;

namespace db_interface {

    db_handler::db_handler(const char *db_file, logger::logger *lgr) {
        _lgr = lgr;
        int ret_code = sqlite3_open_v2(db_file, &_db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

        if (ret_code == SQLITE_OK) {
            lgr->log("Connected to DB file " + (string)db_file);
        } else {
            string msg = "Failed to open DB file " + (string)db_file + " with code " + std::to_string(ret_code);
            lgr->log(msg, logger::PANIC);
            exit(1);
        }

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

        int ret_code = sqlite3_prepare_v2(_db, cmd, -1, &stmt, nullptr);
        if (ret_code == SQLITE_OK) {
            _lgr->log("Initialization command prepared.", logger::DEBUG);
        } else {
            _lgr->log("Failed to prepare initialization command", logger::PANIC);
            exit(1);
        }

        ret_code = sqlite3_step(stmt);
        if (ret_code == SQLITE_DONE) {
            _lgr->log("Todos table initialized.");
        } else {
            _lgr->log("Failed to initialize todos table.", logger::PANIC);
            exit(1);
        }

        sqlite3_finalize(stmt);
    }

    void db_handler::handle_ret_code(int ret_code) {
    }
}
