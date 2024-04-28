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
    };

    class db_handler {
        public:
            db_handler(const char *db_file, logger::logger *lgr);
            ~db_handler();

            std::vector<todo> get_todos();
            todo get_todo(int id);
            int add_todo(std::string todo_text);
            int update_todo(todo new_todo);
            int delete_todo(int id);
            int strikethrough_todo(int id);

        private:
            sqlite3 *_db;
            logger::logger *_lgr;
            void _initialize_db();
            void _execute_cmd(const char *cmd, std::string cmd_desc, bool is_critical = false);
    };

}

#endif // DB_INTERFACE_HPP_DEFINED
