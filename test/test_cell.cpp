#include <engine/cell.h>
#include <assert.h>
#include <iostream>

using namespace minesweeper;

void test_creation(){
    cell c();
    cell c2(cell_type::BOMB);
    cell c3(cell_type::NUMERED);

    assert(c.clicked() == false);
    assert(c2.clicked() == false);
    assert(c3.clicked() == false);

    assert(c.marked() == false);
    assert(c2.marked() == false);
    assert(c3.marked() == false);

    assert(c.type() == cell_type::EMPTY);
    assert(c2.type() == cell_type::NUMERED);
    assert(c3.type() == cell_type::BOMB);
}

void test_click_and_mark(){
    cell c();

    c.click();
    assert(c.clicked() == true);

    c.mark();

    assert(c.marked() == true);

    c.unmark();

    assert(c.marked() == false);
}

void test_type_and_bombs(){
    cell c();

    assert(c.type() == cell_type::EMPTY);

    c.set_type(cell_type::NUMERED);

    assert(c.type() == cell_type::NUMERED);

    c.set_bombs_next(4);

    assert(c.get_bombs_next() == 4);

    c.set_bombs_next(20);

    assert(c.get_bombs_next() == 8);

    c.set_bombs_next(-30);

    assert(c.get_bombs_next() == 0);
}

int main(void){

    test_creation();
    test_click_and_mark();
    test_type_and_bombs();

    return 0;
}