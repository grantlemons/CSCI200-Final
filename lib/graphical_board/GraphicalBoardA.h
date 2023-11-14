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
 * @class GraphicalBoardA
 * Abstract class representation of a Tic-Tac-Toe board's graphical elements.
 *
 * Contains functionality for drawing Tic-Tac-Toe boards as well as marking
 * their cells.
 */
class GraphicalBoardA : virtual public GraphicalBoardI {
protected:
    /** The handler object used to access the underlying
     * notcurses instance.
     */
    NcHandlerI *mncHandler;

    /** The primary plane used as a canvas for drawing the board. */
    NcPlaneWrapperI *mprimaryPlane;

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
    std::array<std::unique_ptr<GraphicalAreaI>, CELL_COUNT> mchildren;

    /** The height of the primary plane */
    int mrows;
    /** The width of the primary plane */
    int mcols;

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
    GraphicalBoardA(NcHandlerI *const P_ncHandler, int const Y, int const X,
                    int const ROWS, int const COLS);

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
    GraphicalBoardA(NcHandlerI *const P_ncHandler, ncplane_options const NOPTS);

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
    GraphicalBoardA(NcHandlerI *const P_ncHandler,
                    NcPlaneWrapperI *const P_plane);

    /**
     * Virtual function for initializing child planes.
     *
     * Implemented differently for PrimaryGraphicalBoard and LeafGraphicalBoard.
     */
    virtual void init_child_planes() = 0;

public:
    GraphicalBoardA(GraphicalBoardA &) = delete;
    void operator=(GraphicalBoardA const &) = delete;
    ~GraphicalBoardA() override = default;

    void draw_board(std::array<char const *, SYMBOL_COUNT> const SYMBOLS,
                    uint64_t const CELL_CHANNELS) override final;
    void draw_x(int const INDEX) override;
    void draw_o(int const INDEX) override;
    std::array<GraphicalAreaI *, CELL_COUNT> get_children() override final;

    // Inherited methods of NcPlaneWrapperI
    void dim_yx(int &ROWS, int &COLS) const override final;
    [[nodiscard]] int get_rows() const override final;
    [[nodiscard]] int get_cols() const override final;

    GraphicalAreaI *create_child(ncplane_options const *nopts) override final;

    int load_nccell(nccell *const P_c, char const *gcluster) override final;
    int set_base_cell(nccell const *const P_c) override final;

    int cursor_move_yx(int const X, int const Y) override final;
    int hline(nccell const *const P_c, unsigned const LEN) override final;
    int vline(nccell const *const P_c, unsigned const LEN) override final;
    int putc_yx(int const Y, int const X,
                nccell const *const P_c) override final;
    void erase() override final;
};

#endif // !G_BOARD
