#include <engine/grid/grid.h>
#include <iostream>
using namespace minesweeper;

void test_print(){
    grid g(9, 9);
    g.set_bombs(7);
    
    std::cout << g << std::endl;
    std::cout << std::endl;

    grid_click_t click = {0, 5, true};

    g.init(click);

    std::cout << g << std::endl;
    std::cout << std::endl;

    click.x = 3;
    click.mark = false;

    g.process(click);

    std::cout << g << std::endl;
    std::cout << std::endl;

    std::cout << "range click: " << std::endl;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            click.x = i;
            click.y = j;

            g.process(click);

            std::cout << g << std::endl;
            std::cout << std::endl;
        }
    }

}

int main(void){

    test_print();
    return 0;
}