#include "src/utilities.hpp"
#include "src/cmd_handler.hpp"
#include <string>

int main(int argc, char *argv[]) {

    std::string log_file_path = utilities::get_app_file_path("todos.log");
    std::string db_file_path = utilities::get_app_file_path("todos.db");
    cmd_interface::cmd_handler *handler = new cmd_interface::cmd_handler(log_file_path, db_file_path);
    handler->handle_cmd(argc, argv);

    return 0;
}
