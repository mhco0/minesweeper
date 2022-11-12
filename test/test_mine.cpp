#include <engine/mine/mine.h>
using namespace minesweeper;

void test_game(){
    mine game;

    grid_click_t click = {0, 0, false};

    game.start();

    game.update(click);
}

int main(void){

    test_game();
    return 0;
}