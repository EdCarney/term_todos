#ifndef DB_INTERFACE_HPP_DEFINED
#define DB_INTERFACE_HPP_DEFINED

#include "logger.hpp"
#include <sqlite3.h>
#include <string>
#include <vector>

namespace db_interface {

    struct todo {
        int id;
        std::string text;
        bool checked;
    };

    class db_handler {
        public:
            db_handler(const char *db_file, logger::logger *lgr);
            ~db_handler();

            std::vector<todo> get_todos();
            todo get_todo(int id);
            void add_todo(std::string todo_text);
            void update_todo_text(int id, std::string todo_text);
            void toggle_todo_checked(int id);
            void delete_todo(int id);
            void strikethrough_todo(int id);

        private:
            sqlite3 *_db;
            logger::logger *_lgr;
            void _initialize_db();
            sqlite3_stmt *_prepare_cmd(const char *cmd, std::string cmd_desc, bool is_critical = false);
            int _execute_cmd(sqlite3_stmt *stmt, std::string cmd_desc, bool is_critical = false);
            todo _extract_todo(sqlite3_stmt *stmt);
            void _update_todo(todo new_todo);
    };

}

#endif // DB_INTERFACE_HPP_DEFINED
