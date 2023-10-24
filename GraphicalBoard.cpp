#include "GraphicalBoard.h"
#include "NcHandler.h"

#include <notcurses/notcurses.h>
#include <unistd.h>
#include <memory>
#include <vector>

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
                               const char **const SYMBOLS)
    : GraphicalBoard::GraphicalBoard(
          ncHandler, nopts, ncplane_create(ncHandler->get_stdplane(), &nopts),
          CELL_CHANNELS, SYMBOLS) {}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               ncplane_options nopts, ncplane *const PLANE,
                               const uint64_t CELL_CHANNELS,
                               const char **const SYMBOLS) {
    this->_rows = nopts.rows;
    this->_cols = nopts.cols;

    this->_symbols = SYMBOLS;
    this->_cell_channels = CELL_CHANNELS;
    this->_ncHandler = ncHandler;
    this->_primaryPlane = PLANE;

    const unsigned int ROWS_PER_BCELL = (_rows - 2) / 3;
    const unsigned int COLS_PER_BCELL = (_cols - 2) / 3;

    std::vector<ncplane *> childTmp;
    childTmp.reserve(9);

    for (int i = 0; i < 9; i++) {
        unsigned int row = i % 3;
        unsigned int column = (i - row) / 3;

        unsigned int newX = ROWS_PER_BCELL * row + row + 1;
        unsigned int newY = COLS_PER_BCELL * column + column + 1;

        ncplane_options child_nopts =
            create_nopts(newY, newX, ROWS_PER_BCELL, COLS_PER_BCELL);

        childTmp.push_back(ncplane_create(this->_primaryPlane, &child_nopts));
    }
    this->_childPlanes = childTmp.data();
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
    nccell_load(_primaryPlane, &HORI_CELL, _symbols[0]);
    nccell_load(_primaryPlane, &VERT_CELL, _symbols[1]);
    nccell_load(_primaryPlane, &JUNC_CELL, _symbols[2]);
    nccell_set_channels(&HORI_CELL, _cell_channels);
    nccell_set_channels(&VERT_CELL, _cell_channels);
    nccell_set_channels(&JUNC_CELL, _cell_channels);

    // draw horizontal lines
    res |= ncplane_cursor_move_yx(_primaryPlane, H_IDX_1, X);
    res |= ncplane_hline(_primaryPlane, &HORI_CELL, H_LINE_LEN);

    res |= ncplane_cursor_move_yx(_primaryPlane, H_IDX_2, X);
    res |= ncplane_hline(_primaryPlane, &HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    res |= ncplane_cursor_move_yx(_primaryPlane, Y, V_IDX_1);
    res |= ncplane_vline(_primaryPlane, &VERT_CELL, V_LINE_LEN);

    res |= ncplane_cursor_move_yx(_primaryPlane, Y, V_IDX_2);
    res |= ncplane_vline(_primaryPlane, &VERT_CELL, V_LINE_LEN);

    // draw junction points
    res |= ncplane_putc_yx(_primaryPlane, H_IDX_1, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(_primaryPlane, H_IDX_1, V_IDX_2, &JUNC_CELL);

    res |= ncplane_putc_yx(_primaryPlane, H_IDX_2, V_IDX_1, &JUNC_CELL);
    res |= ncplane_putc_yx(_primaryPlane, H_IDX_2, V_IDX_2, &JUNC_CELL);

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

ncplane **GraphicalBoard::get_child_planes() {
    return this->_childPlanes;
}
