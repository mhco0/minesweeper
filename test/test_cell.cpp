#include <engine/cell/cell.h>
#include <assert.h>
#include <iostream>

using namespace minesweeper;

void test_creation(){
    cell c;
    cell c2(cell_type::BOMB);
    cell c3(cell_type::NUMBERED);

    assert(c.clicked() == false);
    assert(c2.clicked() == false);
    assert(c3.clicked() == false);

    assert(c.marked() == false);
    assert(c2.marked() == false);
    assert(c3.marked() == false);

    assert(c.type() == cell_type::EMPTY);
    assert(c2.type() == cell_type::BOMB);
    assert(c3.type() == cell_type::NUMBERED);
}

void test_click_and_mark(){
    cell c;

    c.click();
    assert(c.clicked() == true);

    c.mark();

    assert(c.marked() == true);

    c.unmark();

    assert(c.marked() == false);
}

void test_type_and_bombs(){
    cell c;

    assert(c.type() == cell_type::EMPTY);

    c.set_type(cell_type::NUMBERED);

    assert(c.type() == cell_type::NUMBERED);

    c.set_bombs_next(4);

    assert(c.get_bombs_next() == 4);

    c.set_bombs_next(20);

    assert(c.get_bombs_next() == 8);

    c.set_bombs_next(-30);

    assert(c.get_bombs_next() == 0);
}

void test_print(){
    cell c;

    c.click();

    std::cout << c << std::endl;

    c.set_type(cell_type::NUMBERED);

    std::cout << c << std::endl;

    c.set_bombs_next(4);

    std::cout << c << std::endl;

    c.set_type(cell_type::BOMB);

    std::cout << c << std::endl;

    c.mark();

    std::cout << c << std::endl;
}

int main(void){

    test_creation();
    test_click_and_mark();
    test_type_and_bombs();
    test_print();

    return 0;
}