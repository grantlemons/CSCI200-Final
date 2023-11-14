#ifndef LEAF_G_BOARD
#define LEAF_G_BOARD

#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/interfaces/NcHandlerI.h"

#include <memory>
#include <notcurses/notcurses.h>

class LeafGraphicalBoard : virtual public GraphicalBoardA {
private:
    void init_child_planes() override final;

public:
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
    LeafGraphicalBoard(NcHandlerI *ncHandler, const int Y, const int X,
                       const int ROWS, const int COLS);

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
    LeafGraphicalBoard(NcHandlerI *const ncHandler,
                       const ncplane_options NOPTS);

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
    LeafGraphicalBoard(NcHandlerI *const ncHandler,
                       NcPlaneWrapperI *const PLANE);
};

#endif
