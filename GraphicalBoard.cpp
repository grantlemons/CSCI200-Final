#include "GraphicalBoard.h"
#include "NcHandler.h"

#include <notcurses/notcurses.h>
#include <unistd.h>
#include <memory>

ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS) {
    ncplane_options nopts = {
        (int)Y, (int)X, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };

    return nopts;
}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               const int Y, const int X,
                               const unsigned int ROWS, const unsigned int COLS,
                               const uint64_t CELL_CHANNELS,
                               const char **const SYMBOLS)
    : GraphicalBoard::GraphicalBoard(ncHandler, create_nopts(Y, X, ROWS, COLS),
                                     CELL_CHANNELS, SYMBOLS) {}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               ncplane_options nopts,
                               const uint64_t CELL_CHANNELS,
                               const char **const SYMBOLS) {
    this->_y = nopts.y;
    this->_x = nopts.x;
    this->_rows = nopts.rows;
    this->_cols = nopts.cols;

    this->_symbols = SYMBOLS;
    this->_cell_channels = CELL_CHANNELS;
    this->_ncHandler = ncHandler;

    ncplane *std = this->_ncHandler->get_stdplane();
    this->_plane = ncplane_create(std, &nopts);
}

int GraphicalBoard::draw_board_yx(const int Y, const int X,
                                  const unsigned int ROWS_PER_BCELL,
                                  const unsigned int COLS_PER_BCELL) {
    int res = EXIT_SUCCESS;

    // calculate lines positions and lengths
    const unsigned int H_IDX_1 = Y + ROWS_PER_BCELL;
    const unsigned int H_IDX_2 = Y + (2 * ROWS_PER_BCELL);

    const unsigned int V_IDX_1 = X + COLS_PER_BCELL;
    const unsigned int V_IDX_2 = X + (2 * COLS_PER_BCELL);

    const unsigned int H_LINE_LEN = (3 * COLS_PER_BCELL) + 1;
    const unsigned int V_LINE_LEN = (3 * ROWS_PER_BCELL) + 1;

    // define cells
    nccell HORI_CELL, VERT_CELL, JUNC_CELL;
    HORI_CELL = VERT_CELL = JUNC_CELL = NCCELL_TRIVIAL_INITIALIZER;
    nccell_load(_plane, &HORI_CELL, _symbols[0]);
    nccell_load(_plane, &VERT_CELL, _symbols[1]);
    nccell_load(_plane, &JUNC_CELL, _symbols[2]);
    nccell_set_channels(&HORI_CELL, _cell_channels);
    nccell_set_channels(&VERT_CELL, _cell_channels);
    nccell_set_channels(&JUNC_CELL, _cell_channels);

    // draw horizontal lines
    res |= ncplane_cursor_move_yx(_plane, H_IDX_1, X);
    res |= ncplane_hline(_plane, &HORI_CELL, H_LINE_LEN);

    res |= ncplane_cursor_move_yx(_plane, H_IDX_2, X);
    res |= ncplane_hline(_plane, &HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    res |= ncplane_cursor_move_yx(_plane, Y, V_IDX_1);
    res |= ncplane_vline(_plane, &VERT_CELL, V_LINE_LEN);

    res |= ncplane_cursor_move_yx(_plane, Y, V_IDX_2);
    res |= ncplane_vline(_plane, &VERT_CELL, V_LINE_LEN);

    // draw junction points
    res |= ncplane_putc_yx(_plane, H_IDX_1, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(_plane, H_IDX_1, V_IDX_2, &JUNC_CELL);

    res |= ncplane_putc_yx(_plane, H_IDX_2, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(_plane, H_IDX_2, V_IDX_2, &JUNC_CELL);

    return res;
}
// int GraphicalBoard::draw_x_yx(const int Y, const int X) {}
// int GraphicalBoard::draw_o_yx(const int Y, const int X) {}

void GraphicalBoard::draw_board() {
    const unsigned int ROWS_PER_BCELL = (_rows - 2) / 3;
    const unsigned int COLS_PER_BCELL = (_cols - 2) / 3;

    draw_board_yx(0, 0, ROWS_PER_BCELL, COLS_PER_BCELL);
    _ncHandler->render();
}

// void GraphicalBoard::draw_x(const unsigned int INDEX) {}
// void GraphicalBoard::draw_o(const unsigned int INDEX) {}
