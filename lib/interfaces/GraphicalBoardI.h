#ifndef G_BOARDI
#define G_BOARDI

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <cstdint>
#include <memory>

class GraphicalBoardI {
public:
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
    draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
               const uint64_t CELL_CHANNELS) = 0;

    /**
     * Marks a cell at an index as belonging to the X player.
     *
     * @param INDEX The index of the cell to mark.
     */
    virtual void draw_x(const unsigned int INDEX) = 0;

    /**
     * Marks a cell at an index as belonging to the O player.
     *
     * @param INDEX The index of the cell to mark.
     */
    virtual void draw_o(const unsigned int INDEX) = 0;

    /**
     * Marks all cells as belonging to the X player.
     */
    virtual void fill_x() = 0;

    /**
     * Marks all cells as belonging to the O player.
     */
    virtual void fill_o() = 0;

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
    virtual std::array<NcPlaneWrapperI *, CELL_COUNT> *get_child_planes() = 0;

    /**
     * Initializes a new GraphicalBoard for each child plane.
     *
     * @return An array of unique pointers to GraphicalBoards.
     */
    virtual std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
    create_child_boards() const = 0;
};
#endif
