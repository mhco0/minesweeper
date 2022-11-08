#include <engine/cell.h>

namespace minesweeper {

cell::cell(const cell_type& ct){
    this->m_clicked = false;
    this->m_type = ct;
}

void cell::click(){
    this->m_clicked = true;
}

bool cell::clicked(){
    return this->m_clicked;
}

}