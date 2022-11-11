cmake_minimum_required(VERSION 3.19)

project(minesweeper_engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

configure_file(minesweeper_engine_config.h.in minesweeper_engine_config.h)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)