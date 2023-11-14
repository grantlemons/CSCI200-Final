#ifndef G_BOARDI
#define G_BOARDI

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <cstdint>

/**
 * @class IGraphicalBoard
 * Interface for graphical board classes.
 *
 * @see AGraphicalBoard
 * @see GraphicalBoardDummy
 */
class IGraphicalBoard : virtual public IGraphicalArea {
public:
    ~IGraphicalBoard() override = default;

    /**
     * Draws a Tic-Tac-Toe board on the primary plane.
     *
     * @param SYMBOLS The unicode characters used to draw the lines of the
     * board. The indexes (in order) are the character for horizontal lines,
     * vertical lines, and junctions between lines.
     * @param CELL_CHANNELS The default forground and background channels for
     * the board.
     *
     * @see ncplane_hline()
     * @see ncplane_vline()
     */
    virtual void
    draw_board(std::array<char const *, SYMBOL_COUNT> const SYMBOLS,
               uint64_t const CELL_CHANNELS) = 0;

    /**
     * Marks a cell at an index as belonging to the X player.
     *
     * @param INDEX The index of the cell to mark.
     */
    virtual void draw_x(int const INDEX) = 0;

    /**
     * Marks a cell at an index as belonging to the O player.
     *
     * @param INDEX The index of the cell to mark.
     */
    virtual void draw_o(int const INDEX) = 0;

    /**
     * Getter for the board's child planes.
     *
     * Child planes contain the planes for the cells in order from left to
     * right, top to bottom.
     *
     * Layout:
     * 0|1|2
     * 3|4|5
     * 6|7|8
     */
    virtual std::array<IGraphicalArea *, CELL_COUNT> get_children() = 0;
};
#endif
