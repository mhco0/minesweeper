#ifndef __MINE_H__
#define __MINE_H__ 1
#include "../grid/grid.h"

namespace minesweeper {

/**
 * @enum mine_difficulty
 * @brief A simple enum to describe the difficults levels on the minesweeper game
 * @details The game has three difficults: easy, medium and hard. Each difficult sets
 * the size of the grid on the minesweeper game and the numbers of the bombs on it.
 * The dev difficult on the minesweeper isn't intend to be on the game. It's only used
 * on debug mode.
*/
enum class mine_difficulty {
    easy = 0,
    medium, 
    hard, 
    dev
};

/**
 * @enum game_state
 * @brief A simple enum to describe the game state of the minesweeper
 * @details The game state starts on setup to set the difficult of the game. Doing that we 
 * start on a loop where each action updates the game state. Afther that the game can go to 
 * two states, a defeat state if we click in a bomb and a victory state if we clean the board 
 * with no bombs in it. 
*/
enum class game_state {
    setup = 0, 
    playing,
    victory,
    defeat
};

/**
 * @class mine
 * @brief A class that represents the minesweeper engine.
 * @details The minesweeper engine has all propertys to play a simple minesweeper game.
 * It holds the game difficulty and the game state with the actions of a player on it.
 * It also handle all actions and updates the game state in according.
 * @see void mine::start();
 * @see void mine::update(const grid_click_t&);
 * @see grid_click_t
*/
class mine {
protected:
    mine_difficulty m_difficulty;
    game_state m_state;
    grid* m_grid;
    int m_bombs;
    int m_grid_width;
    int m_grid_height;
public:

    /**
     * @brief A constructor for the minesweeper engine
    */
    mine();

    /**
     * @brief A destructor for the minesweeper engine
    */
    virtual ~mine();

    /**
     * @brief A member function to set the difficult of the game
     * @param difficult The desired game difficulty
    */
    void set_difficulty(const mine_difficulty& difficulty);

    /**
     * @brief A member function to starts the game
    */
    void start();

    /**
     * @brief A member function to update the game with some click on the grid
     * @param action The click on the grid representing some action
    */
    void update(const grid_click_t& action);

    /**
     * @brief A member function that returns the current game state
     * @return The current game state
    */
    game_state get_game_state();
};

}
#endif