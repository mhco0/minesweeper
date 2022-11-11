#include <engine/cell/cell.h>
#include <algorithm>

namespace minesweeper {

cell::cell(){
    this->m_clicked = false;
    this->m_marked = false;
    this->m_bombs_next = 0;
    this->m_type = cell_type::EMPTY;
}

cell::cell(const cell_type& ct): cell(){
    this->m_type = ct;
}

void cell::click(){
    this->m_clicked = true;
}

void cell::mark(){
    this->m_marked = true;
}

void cell::unmark(){
    this->m_marked = false;
}

void cell::set_bombs_next(const int& bombs){
    if(this->m_type == cell_type::NUMBERED){
        this->m_bombs_next = std::max(0, std::min(8, bombs));
    }
}

int cell::get_bombs_next(){
    return this->m_bombs_next;
}

bool cell::marked(){
    return this->m_marked;
}

bool cell::clicked(){
    return this->m_clicked;
}

void cell::set_type(const cell_type& type){
    this->m_type = type;
}

cell_type cell::type(){
    return this->m_type;
}

std::ostream& operator<<(std::ostream& os, cell& c){
    if(c.marked()){
        return os << 'M';
    }

    if(!c.clicked()){
        return os << '#'; 
    }
    
    switch(c.type()){
        case cell_type::BOMB:{
            os << 'B';
        }
        break;
        case cell_type::NUMBERED:{
            os << (char) (c.get_bombs_next() + '0');
        }
        break;
        case cell_type::EMPTY:{
            os << ' ';
        }
        break;
        default:{
            os << 'U'; // unkown dehavier 
        }
        break;
    }

    return os;
}

}

