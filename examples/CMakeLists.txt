add_executable(minesweeper_game minesweeper_game.cpp)

target_include_directories(minesweeper_game PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(minesweeper_game PUBLIC minesweeper_engine_mine)