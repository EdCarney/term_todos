cmake_minimum_required(VERSION 3.23)
project(Term_Todos VERSION 1.0.0)

find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(This todos)
set(Sources
    main.cpp
    src/db_handler.hpp
    src/db_handler.cpp
    src/logger.hpp
    src/logger.cpp
    src/utilities.hpp
    src/utilities.cpp
    src/cmd_handler.hpp
    src/cmd_handler.cpp)

add_executable(${This} ${Sources})
target_link_libraries(${This} SQLite::SQLite3)
