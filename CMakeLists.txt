cmake_minimum_required(VERSION 3.19)

project(minesweeper_engine VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(USE_GUI "Configures if the project will use the gui or not" OFF)

configure_file(minesweeper_engine_config.h.in minesweeper_engine_config.h)

if(USE_GUI)
    add_subdirectory(thirdyparty/SFML)
    include_directories("${CMAKE_SOURCE_DIR}/thirdyparty/SFML/include")
endif()

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
