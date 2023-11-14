#ifndef G_BOARD
#define G_BOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/GraphicalBoardI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

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
class GraphicalBoardA : virtual public GraphicalBoardI {
protected:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    NcHandlerI *_ncHandler;

    /** The primary plane used as a canvas for drawing the board. */
    NcPlaneWrapperI *_primaryPlane;

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
    std::array<std::unique_ptr<GraphicalAreaI>, CELL_COUNT> _children;

    /** The height and width of the primary plane */
    int _rows, _cols;

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
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoardA(NcHandlerI *const ncHandler, const int Y, const int X,
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
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoardA(NcHandlerI *const ncHandler, const ncplane_options NOPTS);

    /**
     * A constructor that takes in an notcurses plane and uses it as its primary
     * plane.
     *
     * Creates child planes used for the cells of the board.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param PLANE The plane used as the primary plane.
     *
     * @see _primaryPlane
     * @see _childPlanes
     */
    GraphicalBoardA(NcHandlerI *const ncHandler, NcPlaneWrapperI *const PLANE);

    virtual void init_child_planes() = 0;

public:
    GraphicalBoardA(GraphicalBoardA &) = delete;
    void operator=(const GraphicalBoardA &) = delete;
    ~GraphicalBoardA() = default;

    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const int INDEX) override final;
    void draw_o(const int INDEX) override final;
    void fill_x() override final;
    void fill_o() override final;
    std::array<GraphicalAreaI *, CELL_COUNT> get_children() override final;

    // Inherited methods of NcPlaneWrapperI
    void dim_yx(int &ROWS, int &COLS) const override final;
    int get_rows() const override final;
    int get_cols() const override final;

    GraphicalAreaI *create_child(const ncplane_options *nopts) override final;

    int load_nccell(nccell *const c, const char *gcluster) override final;
    int set_base_cell(const nccell *const c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const c, const unsigned LEN) override final;
    int vline(const nccell *const c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X, const nccell *const c) override final;
    void erase() override final;
};

#endif // !G_BOARD
