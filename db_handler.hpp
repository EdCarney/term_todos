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
            db_handler(const char *db_file);
            ~db_handler();

            std::vector<todo> get_todos();
            todo get_todo(int id);
            int add_todo(std::string todo_text);
            int update_todo(todo new_todo);
            int delete_todo(int id);
            int strikethrough_todo(int id);

        private:
            sqlite3 *db;
            void handle_ret_code(int ret_code);
            void initialize_db();
    };

}
