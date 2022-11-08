#include <assert.h>
#include <engine/grid.h>

namespace minesweeper{

grid::grid(const int& width, const int height){
    this->m_width = width;
    this->m_height = height;
    this->m_cells_sz = width * height;   
    this->m_cells = nullptr;
    this->m_bombs = 0;
    this->m_started = false;

    if(!this->m_width or !this->m_height) return;

    this->m_cells = new cell[this->m_cells_sz]();
}

grid::~grid(){
    if(this->m_cells){
        delete this->m_cells;
    }
}

void grid::set_boombs(const int& bombs){
    this->m_bombs = bombs;
}

void grid::init(const grid_click_t& initial_click){
    assert(initial_click.x < this->m_width and initial_click.x >= 0);
    assert(initial_click.y < this->m_height and initial_click.y >= 0);

    if(this->m_started) return;

    // saves initial click as safe spot
    // randomize bombs into grid position
    // process each cell on grid based on bomb already defined positions
    // if the click is a empty cell expand the grid view (mark cells as clicked)

    this->m_started = true;
}

void grid::process(const grid_click_t& click){
    assert(initial_click.x < this->m_width and initial_click.x >= 0);
    assert(initial_click.y < this->m_height and initial_click.y >= 0);

    if(!this->m_started){
        this->init(click);
    }

    size_t index = click.x * this->m_width + click.y;

    if(click.mark){
        // just mark the cell
        if(this->m_cells[index].marked()) // add here the possibility of unmark the cell
        else this->m_cells[index].mark();
    }else{
        this->m_cells[index].click();
        // expands grid here
    }

    return;
}

}