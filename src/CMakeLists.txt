add_library(minesweeper_engine_cell engine/cell/cell.cpp)
target_include_directories(minesweeper_engine_cell PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_library(minesweeper_engine_grid engine/grid/grid.cpp)
target_include_directories(minesweeper_engine_grid PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(minesweeper_engine_grid PUBLIC minesweeper_engine_cell)

add_library(minesweeper_engine_mine engine/mine/mine.cpp)
target_include_directories(minesweeper_engine_mine PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(minesweeper_engine_mine PUBLIC minesweeper_engine_grid)

