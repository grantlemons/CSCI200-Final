#ifndef PRIMARY_G_BOARD
#define PRIMARY_G_BOARD

#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <notcurses/notcurses.h>

/**
 * @class PrimaryGraphicalBoard
 * GraphicalBoard class with LeafGraphicalBoards for cells.
 *
 * @see PrimaryBoard
 * @see LeafGraphicalBoard
 */
class PrimaryGraphicalBoard : virtual public GraphicalBoardA {
private:
    void init_child_planes() override final;

public:
    ~PrimaryGraphicalBoard() override;

    /**
     * A constructor that takes in the raw info for a plane and forms its
     * primary plane from those options.
     *
     * Calls the constructor that takes an ncplane_options struct.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     *
     * @see create_nopts()
     */
    PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler, int const Y,
                          int const X, int const ROWS, int const COLS);

    /**
     * A constructor that takes in an ncplane_options struct for a plane and
     * forms its primary plane from those options.
     *
     * Calls the constructor that takes an ncplane pointer.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     *
     * @see ncplane_create()
     */
    PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler,
                          ncplane_options const NOPTS);

    /**
     * A constructor that takes in an notcurses plane and uses it as its primary
     * plane.
     *
     * Creates child planes used for the cells of the board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane.
     */
    PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler,
                          NcPlaneWrapperI *const P_plane);

    void draw_x(int const INDEX) override final;
    void draw_o(int const INDEX) override final;

    /**
     * Marks all cells of a child board as belonging to the X player.
     *
     * @param INDEX The index of the child board to mark.
     */
    void fill_x(int const INDEX);

    /**
     * Marks all cells of a child board as belonging to the O player.
     *
     * @param INDEX The index of the child board to mark.
     */
    void fill_o(int const INDEX);
};

#endif
