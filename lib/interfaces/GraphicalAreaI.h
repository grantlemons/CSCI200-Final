#ifndef GRAPHICAL_AREAI
#define GRAPHICAL_AREAI

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class GraphicalAreaI
 * Top-Level interface for all things graphical.
 */
class GraphicalAreaI {
public:
    virtual ~GraphicalAreaI() = default;

    /**
     * Get the dimensions of the drawing area.
     */
    virtual void dim_yx(int &ROWS, int &COLS) const = 0;

    /**
     * Get the height of the drawing area.
     */
    [[nodiscard]] virtual int get_rows() const = 0;

    /**
     * Get the width of the drawing area.
     */
    [[nodiscard]] virtual int get_cols() const = 0;

    /**
     * Create another GraphicalAreaI from the current one.
     */
    virtual GraphicalAreaI *create_child(ncplane_options const *nopts) = 0;

    /**
     * Set a notcurses cell to have a specific gcluster.
     *
     * Very notcurses specific.
     */
    virtual int load_nccell(nccell *const P_c, char const *gcluster) = 0;

    /**
     * Set the base cell of the graphical area to the input.
     */
    virtual int set_base_cell(nccell const *const P_c) = 0;

    /**
     * Move the cursor to a yx cell coordinate on the terminal.
     *
     * @param X The X coordinate of the target cell.
     * @param Y The Y coordinate of the target cell.
     */
    virtual int cursor_move_yx(int const X, int const Y) = 0;

    /**
     * Draw a horizontal line with a certain cell for a specified length.
     *
     * @param c The cell to draw with.
     * @param LEN The length of the line drawn.
     */
    virtual int hline(nccell const *const P_c, unsigned const LEN) = 0;

    /**
     * Draw a vertical line with a certain cell for a specified length.
     *
     * @param c The cell to draw with.
     * @param LEN The length of the line drawn.
     */
    virtual int vline(nccell const *const P_c, unsigned const LEN) = 0;

    /**
     * Replace an yx cell coordinate on the terminal with the specified cell.
     *
     * @param c The cell to replace with.
     * @param X The X coordinate of the target cell.
     * @param Y The Y coordinate of the target cell.
     */
    virtual int putc_yx(int const Y, int const X, nccell const *const P_c) = 0;

    /**
     * Erase all edits to the graphical area.
     */
    virtual void erase() = 0;
};

#endif
