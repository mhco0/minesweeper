#include <engine/mine/mine.h>
#include <iostream>

namespace minesweeper {

void mine::check_game_state(){
    if(this->m_grid == nullptr){
        return;
    }

    int clicked_cells = 0;
    int grid_size = this->m_grid_height * this->m_grid_width;

    for(int i = 0; i < this->m_grid_height; i++){
        for(int j = 0; j < this->m_grid_width; j++){
            size_t index = i * this->m_grid_width + j;
            if(this->m_grid->m_cells[index].clicked()){
                if(this->m_grid->m_cells[index].type() == cell_type::BOMB){
                    this->m_state = game_state::defeat;
                    return;
                }

                clicked_cells++;
            }
        }
    }

    if(clicked_cells == (grid_size - this->m_bombs)){
        this->m_state = game_state::victory;
    }
}

mine::mine(){
    this->m_grid = nullptr;
    this->m_state = game_state::setup;
    this->set_difficulty(game_difficulty::easy);
}

mine::~mine(){
    if(this->m_grid){
        delete this->m_grid;
    }
}

void mine::set_difficulty(const game_difficulty& difficulty){
    this->m_difficulty = difficulty;
    switch (this->m_difficulty){
        case game_difficulty::easy:{
            this->m_bombs = 10;
            this->m_grid_width = 9;
            this->m_grid_height = 9;
        }
        break;
        case game_difficulty::medium:{
            this->m_bombs = 40;
            this->m_grid_width = 16;
            this->m_grid_height = 16;
        }
        break;
        case game_difficulty::hard:{
            this->m_bombs = 99;
            this->m_grid_width = 24;
            this->m_grid_height = 24;
        }
        break;
        default:{
            // change here later if needed
        }
        break;
    }
    
}

void mine::start(){
    if(this->m_grid){
        delete this->m_grid;
    }

    this->m_grid = new grid(this->m_grid_width, this->m_grid_height);
    this->m_grid->set_bombs(this->m_bombs);

}

void mine::update(const grid_click_t& action){
    this->m_state = game_state::playing;

    this->m_grid->process(action);

    check_game_state();
}

bool mine::valid_move(const grid_click_t& action){
    return !(action.x < 0 || action.x >= this->m_grid_width || action.y < 0 || action.y > this->m_grid_height);
}

void mine::process_end_game(){
    this->m_state = game_state::setup;
}

game_state mine::get_game_state(){
    return this->m_state;
}

std::vector<std::vector<char>> mine::get_grid_as_string(){
    if(this->m_grid == nullptr){
            return {};
        }

        std::vector<std::vector<char>> ret(this->m_grid_height, std::vector<char>(this->m_grid_height, '#')); 
        
        for(int i = 0; i < this->m_grid_height; i++) {
            for(int j = 0; j < this->m_grid_width; j++) {
                size_t index = i * this->m_grid_width + j;

                if(this->m_grid->m_cells[index].marked()){
                    ret[i][j] = 'M';
                    continue;
                }

                if(!this->m_grid->m_cells[index].clicked()){
                    ret[i][j] = '#'; 
                }else{
                    switch(this->m_grid->m_cells[index].type()){
                        case cell_type::BOMB:{
                            ret[i][j] = 'B';
                        }
                        break;
                        case cell_type::NUMBERED:{
                            ret[i][j] = (char) (this->m_grid->m_cells[index].get_bombs_next() + '0');
                        }
                        break;
                        case cell_type::EMPTY:{
                            ret[i][j] = ' ';
                        }
                        break;
                        default:{
                            ret[i][j] = 'U'; // unkown dehavier 
                        }
                        break;
                    }
                }
            }
        }

        return ret;
}

std::ostream& operator<<(std::ostream& os, mine& m){

    return os << (*m.m_grid);
} 

}