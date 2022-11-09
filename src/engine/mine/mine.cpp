#include <engine/mine.h>

namespace minesweeper {

mine::mine(){
    this->m_grid = nullptr;
    this->m_game_state = game_state::setup;
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

    this->m_game_state = game_state::playing;
}

void mine::update(const grid_click_t& action){
    if(this->m_game_state != game_state::playing) return;

    this->m_grid->process(action);

    // needs to handle the game state here
}

game_state mine::get_game_state(){
    return this->m_game_state;
}

}