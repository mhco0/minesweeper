#include <engine/grid/grid.h>
#include <algorithm>
#include <queue>
#include <utility> // std::pair
#include <random>
#include <assert.h> // or <cassert>

namespace minesweeper {

void grid::expand(const int& x, const int& y){
    std::queue<std::pair<int, int>> to_visit;

    to_visit.push({x, y});

    while(!to_visit.empty()){
        std::pair<int, int> cell_pos = to_visit.front();
        to_visit.pop();

        int neighboards[8] = {
            (cell_pos.first - 1) * this->m_width + cell_pos.second,
            cell_pos.first * this->m_width + (cell_pos.second - 1),
            (cell_pos.first + 1) * this->m_width + cell_pos.second,
            cell_pos.first * this->m_width + (cell_pos.second + 1),
            (cell_pos.first - 1) * this->m_width + (cell_pos.second - 1),
            (cell_pos.first - 1) * this->m_width + (cell_pos.second + 1),
            (cell_pos.first + 1) * this->m_width + (cell_pos.second - 1),
            (cell_pos.first + 1) * this->m_width + (cell_pos.second + 1),
        };

        std::pair<int, int> neighboards_pos[8] = {
            {(cell_pos.first - 1) , cell_pos.second},
            {cell_pos.first , (cell_pos.second - 1)},
            {(cell_pos.first + 1) , cell_pos.second},
            {cell_pos.first , (cell_pos.second + 1)},
            {(cell_pos.first - 1) , (cell_pos.second - 1)},
            {(cell_pos.first - 1) , (cell_pos.second + 1)},
            {(cell_pos.first + 1) , (cell_pos.second - 1)},
            {(cell_pos.first + 1) , (cell_pos.second + 1)},
        };

        for(short i = 0; i < 8; i++) {
            if(neighboards[i] < 0 || neighboards[i] >= this->m_cells_sz){
                continue;
            }
            
            if(this->m_cells[neighboards[i]].type() == cell_type::EMPTY || this->m_cells[neighboards[i]].type() == cell_type::NUMBERED){
                this->m_cells[neighboards[i]].click();

                if(this->m_cells[neighboards[i]].type() == cell_type::EMPTY){
                    to_visit.push(neighboards_pos[i]);
                } 
            }
        }
    }

    return;
}

grid::grid(const int& width, const int& height){
    this->m_width = width;
    this->m_height = height;
    this->m_cells_sz = width * height;   
    this->m_cells = nullptr;
    this->m_bombs = 0;
    this->m_started = false;

    if(!this->m_width || !this->m_height){
        return;
    }

    this->m_cells = new cell[this->m_cells_sz]();
}

grid::~grid(){
    if(this->m_cells){
        delete[] this->m_cells;
    }
}

void grid::set_bombs(const int& bombs){
    this->m_bombs = bombs;
}

void grid::init(const grid_click_t& initial_click){
    assert(initial_click.x < this->m_width && initial_click.x >= 0);
    assert(initial_click.y < this->m_height && initial_click.y >= 0);

    if(this->m_started){
        return;
    }

    // saves initial click as safe spot
    size_t click_index = initial_click.x * this->m_width + initial_click.y;

    // randomize bombs into grid position
    std::random_device dev;
    std::seed_seq seed {dev(), dev(), dev(), dev(), dev(), dev(), dev(), dev()};
    std::mt19937 eng(seed);

    int* cells_index = new int[this->m_cells_sz - 1]();
    
    for(size_t i = 0, j = 0; i < this->m_cells_sz - 1; i++, j++){
        if(j == click_index){
            j++;
        }

        cells_index[i] = j;
    }

    std::shuffle(cells_index, cells_index + this->m_cells_sz - 1, eng);

    for(size_t i = 0, j = 0; i < this->m_bombs && j < this->m_cells_sz; i++, j++){
        this->m_cells[cells_index[j]].set_type(cell_type::BOMB);
    }

    // process each cell on grid based on bomb already defined positions

    /*
        -------------
        |B|2|1|1|B|1|
        |2|B|1|1|1|1|
        |1|1|1| | | |
        | | | | | | |
        | |1|2|3|2|1|
        | |1|B|B|B|1|
        -------------
        
        For each cell we need to check the bombs on each position on the cell next to it. 
        We treat each cell on grid as a array, so to match the index of a cell we need to 
        save the index of the array. Ex:

        on position (2, 2) the index on the grid will be 2 * 6 + 2 = 14, so we need to convert
        all the positions (1, 2), (3, 2), (2, 3), (2, 1), (1, 1), (3, 3), (1, 3) and (3, 1) in the 
        array index positions. 
    */

    for(size_t i = 0; i < this->m_height; i++){
        for(size_t j = 0; j < this->m_width; j++){
            size_t cell_index = i * this->m_width + j;

            if(this->m_cells[cell_index].type() == cell_type::BOMB){
                continue;
            }else{
                // checks neightboards
                int neighboards[8] = {
                    (i - 1) * this->m_width + j,
                    i * this->m_width + (j - 1),
                    (i + 1) * this->m_width + j,
                    i * this->m_width + (j + 1),
                    (i - 1) * this->m_width + (j - 1),
                    (i - 1) * this->m_width + (j + 1),
                    (i + 1) * this->m_width + (j - 1),
                    (i + 1) * this->m_width + (j + 1),
                };

                int bombs_next = 0;

                for(short i = 0; i < 8; i++){
                    if(neighboards[i] < 0 || neighboards[i] >= this->m_cells_sz){
                        continue;
                    }
                    
                    if(this->m_cells[neighboards[i]].type() == cell_type::BOMB){
                        bombs_next++;
                    }
                }

                if(bombs_next){
                    this->m_cells[cell_index].set_type(cell_type::NUMBERED);
                    this->m_cells[cell_index].set_bombs_next(bombs_next);
                }
            }
        }
    }

    this->m_started = true;

    if(cells_index){
        delete[] cells_index;
    }

    // process the initial click
    this->process(initial_click);
}

void grid::process(const grid_click_t& click){
    assert(click.x < this->m_width && click.x >= 0);
    assert(click.y < this->m_height && click.y >= 0);

    if(!this->m_started){
        this->init(click);
        return;
    }

    size_t index = click.x * this->m_width + click.y;

    if(click.mark){
        // just mark the cell
        if(this->m_cells[index].marked()){
            this->m_cells[index].unmark();
        }else{
            this->m_cells[index].mark();
        }
    }else{
        if (!this->m_cells[index].marked()){
            this->m_cells[index].click();
        
            // expands grid here
            if(this->m_cells[index].type() == cell_type::EMPTY){
                expand(click.x, click.y);
            }
        }
    }

    return;
}

}

std::ostream& operator<<(std::ostream& os, const minesweeper::grid& gd){

    
    return os;
} 