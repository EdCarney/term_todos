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

        _initialize_db();
    }

    db_handler::~db_handler() {
        int ret_code = sqlite3_close(_db);

        if (ret_code == SQLITE_OK) {
            _lgr->log("DB connection closed");
        } else {
            _lgr->log("Failure to properly close DB", logger::PANIC);
            exit(1);
        }
    }


    std::vector<todo> db_handler::get_todos() {
        return std::vector<todo>(0);
    }

    todo db_handler::get_todo(int id) {
        // get data
        std::string cmd_str = "SELECT rowid,todo FROM todos WHERE rowId = " + std::to_string(id) + ";\0";
        string cmd_desc = "get todo with id " + std::to_string(id);
        sqlite3_stmt *stmt = _execute_cmd(cmd_str.c_str(), cmd_desc);

        // hydrate object
        int todo_id = sqlite3_column_int(stmt, 0);
        string todo_text = string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        return todo { todo_id, todo_text };
    }

    void db_handler::add_todo(std::string todo_text) {
        std::string cmd_str = "INSERT INTO todos (todo) VALUES ('" + todo_text + "');\0";
        string cmd_desc = "create new todo with text '" + todo_text + "'";
        sqlite3_stmt *smtm = _execute_cmd(cmd_str.c_str(), cmd_desc);
    }

    void db_handler::update_todo(todo new_todo) {
        std::string cmd_str = "update todos set todo = '" + new_todo.text
            + "' where rowId = " + std::to_string(new_todo.id) + ";\0";
        string cmd_desc = "updating todo with id " + std::to_string(new_todo.id)
            + " to have text '" + new_todo.text + "'";
        sqlite3_stmt *smtm = _execute_cmd(cmd_str.c_str(), cmd_desc);
    }

    void db_handler::delete_todo(int id) {
        std::string cmd_str = "DELETE FROM todos WHERE rowId = " + std::to_string(id) + ";\0";
        string cmd_desc = "delete todo with id " + std::to_string(id);
        sqlite3_stmt *smtm = _execute_cmd(cmd_str.c_str(), cmd_desc);
    }

    void db_handler::strikethrough_todo(int id) {
    }

    void db_handler::_initialize_db() {
        const char *cmd = "CREATE TABLE IF NOT EXISTS todos (id INT PRIMARY KEY, todo TEXT);\0";
        string cmd_desc = "initialize todos table";
        sqlite3_stmt *stmt = _execute_cmd(cmd, cmd_desc, true);
        sqlite3_finalize(stmt);
    }

    sqlite3_stmt *db_handler::_execute_cmd(const char *cmd, string cmd_desc, bool is_critical) {
        sqlite3_stmt *stmt;
        int ret_code = sqlite3_prepare_v2(_db, cmd, -1, &stmt, nullptr);
        logger::log_level err_level = is_critical ? logger::PANIC : logger::ERROR;

        if (ret_code == SQLITE_OK) {
            _lgr->log("Cmd prepared: " + cmd_desc, logger::DEBUG);
        } else {
            _lgr->log("Failed to prepare cmd: " + cmd_desc, err_level);
            if (is_critical)
                exit(1);
        }

        ret_code = sqlite3_step(stmt);
        if (ret_code == SQLITE_DONE || ret_code == SQLITE_ROW) {
            _lgr->log("Cmd executed: " + cmd_desc);
        } else {
            _lgr->log("Failed to execute cmd: " + cmd_desc, err_level);
            if (is_critical)
                exit(1);
        }

        return stmt;
    }
}
