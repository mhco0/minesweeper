#include <engine/mine/mine.h>

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

    this->m_state = game_state::playing;
}

void mine::update(const grid_click_t& action){
    if(this->m_state != game_state::playing) return;

    this->m_grid->process(action);

    check_game_state();
}

bool mine::valid_move(const grid_click_t& action){
    return !(action.x < 0 || action.x >= this->m_grid_width || action.y < 0 || action.y > this->m_grid_height);
}

game_state mine::get_game_state(){
    return this->m_state;
}

std::ostream& operator<<(std::ostream& os, mine& m){

    return os << (*m.m_grid);
} 

}