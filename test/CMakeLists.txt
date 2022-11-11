add_executable(test_cell test_cell.cpp)
target_link_libraries(test_cell PUBLIC minesweeper_engine_cell)

add_executable(test_grid test_grid.cpp)
target_link_libraries(test_grid PUBLIC minesweeper_engine_grid)

add_executable(test_mine test_mine.cpp)
target_link_libraries(test_mine PUBLIC minesweeper_engine_mine)
