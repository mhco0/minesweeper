#ifndef __CELL_H__
#define __CELL_H__ 1

namespace minesweeper {

/**
 * @enum cell_type
 * @brief A simple enum to describle the cell type
 * @details Each cell has a unique type that depends on it initialization.
 * A cell can be empty if has no bombs attach to it. It can be a numbered cell
 * if it has some bomb in a cell adjacent to it. It can be a bomb cell if the cell
 * have a bomb attach to it. 
*/
enum class cell_type {
    EMPTY = 0,
    NUMBERED,
    BOMB,
};

/**
 * @class cell
 * @brief A simple class to represent a cell on the minesweeper grid 
*/
class cell {
protected:
    bool m_clicked;
    bool m_marked;
    int m_bombs_next;
    cell_type m_type;
public:

    /**
     * @brief The default constructor for a cell. By default a cell is considered as empty.
    */
    cell();

    /**
     * @brief A simple constructor for a cell
     * @param ct The type of the cell
    */
    cell(const cell_type& ct);

    /**
     * @brief A method to represent a click on this cell
    */
    void click();

    /**
     * @brief A method to mark the cell with some flag
    */
    void mark();

    /**
     * @brief A method to unmark the cell 
    */
    void unmark();

    /**
     * @brief A method to set the bombs next to this cell
    */
    void set_bombs_next(const int& bombs);

    /**
     * @brief A method to get the number of bombs next to this cell
    */
    int get_bombs_next();

    /**
     * @brief A method to check if the cell was clicked or not
     * @return True if the cell was clicked and false otherwise
    */
    bool clicked();

    /**
     * @brief A method to check if the cell was marked or not
     * @return True if the cell was marked and false otherwise
    */
    bool marked();

    /**
     * @brief A method to set the type of this cell
     * @param type The new type of the cell
    */
    void set_type(const cell_type& type);

    /**
     * @brief A method to get the type of this cell
     * @return The cell_type of the cell
    */
    cell_type type();
};

}
#endif