#ifndef __GRID_H__
#define __GRID_H__ 1
#include "../cell/cell.h"
#include <iostream>

namespace minesweeper {

/**
 * @struct grid_click_t
 * @brief A simple struct to represent a click on the grid
 * @details This struct handles the positional click on grid, where the x member
 * represents the line coordenate on the grid and the y member represents the collumns coordenates.
 * All values are intergers and 0-index based. The struct can handle if the user use his click just to 
 * mark a cell, this detail is covered by the mark member on the struct.
*/
struct grid_click_t {
    int x, y;
    bool mark = false;
};

/**
 * @class grid
 * @brief A simple class to represent the grid on the minesweeper
 * @details The grid should be a matrix of cells on the minesweeper, so this 
 * class handles all the cells on memory and other grid properties. The user
 * can construct a new grid and starts it with the member function @sa init(const grid_click_t&).
 * @see init(const grid_click_t&)
 * @see process(const grid_click_t&)
*/
class grid {
private:
    grid(const grid& other); ///< Copy constructor is private to not have to handle with memory leak
    grid& operator=(const grid& rhs); ///< Assign operator is private to not have to handle with memory leak

protected:
    int m_height;
    int m_width;
    size_t m_cells_sz;
    cell* m_cells;
    int m_bombs;
    bool m_started;

    /**
     * @brief A method to expand the grid from a empty cell located in the @p x and @p y positions of the grid
     * @param x The x coordenate for the empty cell
     * @param y The y coordenate for the empty cell
    */
    void expand(const int& x, const int& y);

public:

    /**
     * @brief A basic constructor for the minesweeper grid
     * @param width The width of the grid
     * @param height The height of the grid
    */
    grid(const int& width, const int& height);

    /**
     * @brief A simple destructor to clean the cells from memory
    */
    virtual ~grid();

    /**
     * @brief A member function to set the number of cells on the grid
     * @param bombs The number of bombs
    */
    void set_bombs(const int& bombs);

    /**
     * @brief A member function to starts the click on the grid
     * @param initial_click A variable with the initial click position
     * @warning Calling a init method on a already started grid does nothing 
    */
    void init(const grid_click_t& initial_click);

    /**
     * @brief A member function to process each click from the user
     * @param click A variable that holds the click information
    */
    void process(const grid_click_t& click);

    /**
     * @brief A print function to print the grid state
     * @param os The output stream
     * @param gd The grid object to be printed
     * @return The output stream
    */
    friend std::ostream& operator<<(std::ostream& os, const grid& gd);
};

}

#endif 