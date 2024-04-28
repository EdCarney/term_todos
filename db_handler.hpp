#include <sqlite3.h>

namespace db_interface {

    class db_handler {
        public:
            db_handler(const char *db_file);
            ~db_handler();

            int add_todo(const char *todo);
            int update_todo(int id, const char *new_todo);
            int delete_todo(int id);
            int strikethrough_todo(int id);

        private:
            sqlite3 *db;
    };

}
