add_executable(minesweeper_game minesweeper_game.cpp)

target_include_directories(minesweeper_game PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(minesweeper_game PUBLIC minesweeper_engine_mine)

if(USE_GUI)
    target_link_libraries(minesweeper_game PUBLIC sfml-window)
endif()