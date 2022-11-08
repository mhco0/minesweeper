#ifndef __CELL_H__
#define __CELL_H__ 1

namespace minesweeper{

/**
 * @brief A simple enum to describle the cell type
*/
enum class cell_type {
    EMPTY_CELL = 0,
    BOMB,
};

/**
 * @brief A simple class to represent a cell on the minesweeper grid 
*/
class cell{
protected:
    bool m_clicked;
    cell_type m_type;
public:
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
     * @brief A method to check if the cell was clicked or not
    */
    bool clicked();
};

}
#endif