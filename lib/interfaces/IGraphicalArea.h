/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef GRAPHICAL_AREAI
#define GRAPHICAL_AREAI

#include "lib/interfaces/INcHandler.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class IGraphicalArea
 * Top-Level interface for all things graphical.
 */
class IGraphicalArea {
public:
    virtual ~IGraphicalArea() = default;

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
    virtual IGraphicalArea *create_child(const ncplane_options *nopts) = 0;

    /**
     * Set a notcurses cell to have a specific gcluster.
     *
     * Very notcurses specific.
     */
    virtual int load_nccell(nccell *const P_c, const char *gcluster) = 0;

    /**
     * Set the base cell of the graphical area to the input.
     */
    virtual int set_base_cell(const nccell *const P_c) = 0;

    /**
     * Move the cursor to a yx cell coordinate on the terminal.
     *
     * @param X The X coordinate of the target cell.
     * @param Y The Y coordinate of the target cell.
     */
    virtual int cursor_move_yx(const int X, const int Y) = 0;

    /**
     * Draw a horizontal line with a certain cell for a specified length.
     *
     * @param P_c The cell to draw with.
     * @param LEN The length of the line drawn.
     */
    virtual int hline(const nccell *const P_c, const unsigned LEN) = 0;

    /**
     * Draw a vertical line with a certain cell for a specified length.
     *
     * @param P_c The cell to draw with.
     * @param LEN The length of the line drawn.
     */
    virtual int vline(const nccell *const P_c, const unsigned LEN) = 0;

    /**
     * Replace an yx cell coordinate on the terminal with the specified cell.
     *
     * @param P_c The cell to replace with.
     * @param X The X coordinate of the target cell.
     * @param Y The Y coordinate of the target cell.
     */
    virtual int putc_yx(const int Y, const int X, const nccell *const P_c) = 0;

    /**
     * Erase all edits to the graphical area.
     */
    virtual void erase() = 0;
};

#endif
