/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef PRIMARY_G_BOARD
#define PRIMARY_G_BOARD

#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <notcurses/notcurses.h>

/**
 * @class PrimaryGraphicalBoard
 * GraphicalBoard class with LeafGraphicalBoards for cells.
 */
class PrimaryGraphicalBoard : virtual public AGraphicalBoard {
private:
    void init_child_planes() override final;

public:
    /**
     * A constructor that takes in the raw info for a plane and forms its
     * primary plane from those options.
     *
     * Calls the constructor that takes an ncplane_options struct.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     */
    PrimaryGraphicalBoard(INcHandler *const P_ncHandler, const int Y,
                          const int X, const int ROWS, const int COLS);

    /**
     * A constructor that takes in an ncplane_options struct for a plane and
     * forms its primary plane from those options.
     *
     * Calls the constructor that takes an ncplane pointer.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     */
    PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                          const ncplane_options NOPTS);

    /**
     * A constructor that takes in an notcurses plane and uses it as its primary
     * plane.
     *
     * Creates child planes used for the cells of the board.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param P_plane The plane used as the primary plane.
     */
    PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                          std::unique_ptr<INcPlaneWrapper> P_plane);

    void draw_x(const int INDEX) override final;
    void draw_o(const int INDEX) override final;
    void draw_tie(const int INDEX) override final;

    /**
     * Marks all cells of a child board as belonging to the X player.
     *
     * @param INDEX The index of the child board to mark.
     */
    void fill_x(const int INDEX);

    /**
     * Marks all cells of a child board as belonging to the O player.
     *
     * @param INDEX The index of the child board to mark.
     */
    void fill_o(const int INDEX);

    void fill_tie(const int INDEX);
};

#endif
