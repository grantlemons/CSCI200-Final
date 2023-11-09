#ifndef G_BOARD
#define G_BOARD

#include "lib/NcHandler.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

/**
 * @class GraphicalBoard
 * Representation of a Tic-Tac-Toe board's graphical elements.
 *
 * Contains functionality for drawing Tic-Tac-Toe boards as well as marking
 * their cells.
 */
class GraphicalBoard {
private:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    std::shared_ptr<NcHandler> _ncHandler;

    /** The primary plane used as a canvas for drawing the board. */
    ncplane *_primaryPlane;

    /** The child planes used to represent the cells of the board
     *
     * Child planes contain the planes for the cells in order from left to
     * right, top to bottom.
     *
     * Layout:
     * 0|1|2
     * 3|4|5
     * 6|7|8
     */
    std::array<ncplane *, 9> _childPlanes;

    /** The height and width of the primary plane */
    unsigned int _rows, _cols;

    /** The unicode characters used to draw the board */
    std::array<const char *, 3> _symbols;

    /** The default foreground and background color channels */
    uint64_t _cell_channels;

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
     * @param CELL_CHANNELS The default forground and background channels for
     * the board.
     * @param SYMBOLS The unicode characters used to draw the lines of the
     * board. The indexes (in order) are the character for horizontal lines,
     * vertical lines, and junctions between lines.
     *
     * @see create_nopts()
     * @see GraphicalBoard(std::shared_ptr<NcHandler>, const ncplane_options,
     * const uint64_t, std::array<const char *, 3>)
     * @see _primaryPlane
     * @see _childPlanes
     * @see _symbols
     * @see _cell_channels
     */
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, const int Y,
                   const int X, const unsigned int ROWS,
                   const unsigned int COLS, const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);

    /**
     * A constructor that takes in an ncplane_options struct for a plane and
     * forms its primary plane from those options.
     *
     * Calls the constructor that takes an ncplane pointer.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param NOPTS The configuration used to form the primary plane.
     * @param CELL_CHANNELS The default forground and background channels for
     * the board.
     * @param SYMBOLS The unicode characters used to draw the lines of the
     * board. The indexes (in order) are the character for horizontal lines,
     * vertical lines, and junctions between lines.
     *
     * @see ncplane_create()
     * @see GraphicalBoard(std::shared_ptr<NcHandler>, ncplane *const, const
     * uint64_t, std::array<const char *, 3>)
     * @see _primaryPlane
     * @see _childPlanes
     * @see _symbols
     * @see _cell_channels
     */
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                   const ncplane_options NOPTS, const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);

    /**
     * A constructor that takes in an notcurses plane and uses it as its primary
     * plane.
     *
     * Creates child planes used for the cells of the board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane.
     * @param CELL_CHANNELS The default forground and background channels for
     * the board.
     * @param SYMBOLS The unicode characters used to draw the lines of the
     * board. The indexes (in order) are the character for horizontal lines,
     * vertical lines, and junctions between lines.
     *
     * @see _primaryPlane
     * @see _childPlanes
     * @see _symbols
     * @see _cell_channels
     */
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE,
                   const uint64_t CELL_CHANNELS,
                   std::array<const char *, 3> SYMBOLS);

    GraphicalBoard(GraphicalBoard &) = delete;
    void operator=(const GraphicalBoard &) = delete;
    ~GraphicalBoard() = default;

    /**
     * Draws a Tic-Tac-Toe board on the primary plane.
     *
     * @see ncplane_hline()
     * @see ncplane_vline()
     */
    void draw_board();

    /**
     * Marks a cell at an index as belonging to the X player.
     *
     * @param INDEX The index of the cell to mark.
     */
    void draw_x(const unsigned int INDEX);

    /**
     * Marks a cell at an index as belonging to the O player.
     *
     * @param INDEX The index of the cell to mark.
     */
    void draw_o(const unsigned int INDEX);

    /**
     * Marks all cells as belonging to the X player.
     */
    void fill_x();

    /**
     * Marks all cells as belonging to the O player.
     */
    void fill_o();

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
    std::array<ncplane *, 9> get_child_planes() const;
};

// Helper functions

/**
 * Forms an struct describing the configuration of a notcurses plane from the
 * data passed in.
 *
 * @param Y The Y coordinate of the new plane's top left corner.
 * @param X The X coordinate of the new plane's top left corner.
 * @param ROWS The number of rows composing the new plane. (Height)
 * @param COLS The number of columns composing the new plane. (Width)
 * @return An ncplane_options struct describing the configuration options.
 */
ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS);

/**
 * Extracts the configuration used to form the given plane.
 *
 * @param PLANE The plane to extract the configuration from.
 * @return An ncplane_options struct describing the plane's configuration
 * options.
 */
ncplane_options extract_nopts(ncplane *PLANE);

#endif // !G_BOARD
