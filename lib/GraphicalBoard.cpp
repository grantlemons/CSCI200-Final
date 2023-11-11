#include "lib/GraphicalBoard.h"

#include "lib/NcHandler.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>
#include <unistd.h>

ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS) {
    ncplane_options nopts = {
        Y, X, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };

    return nopts;
}

ncplane_options extract_nopts(ncplane *PLANE) {
    unsigned int rows, cols;
    ncplane_dim_yx(PLANE, &rows, &cols);

    int y, x;
    ncplane_yx(PLANE, &y, &x);

    ncplane_options nopts = {
        y, x, rows, cols, NULL, NULL, NULL, 0, 0, 0,
    };

    return nopts;
}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               const int Y, const int X,
                               const unsigned int ROWS, const unsigned int COLS)
    : GraphicalBoard::GraphicalBoard(ncHandler,
                                     create_nopts(Y, X, ROWS, COLS)) {}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               const ncplane_options NOPTS)
    : GraphicalBoard::GraphicalBoard(
          ncHandler, ncplane_create(ncHandler->get_stdplane(), &NOPTS)) {}

GraphicalBoard::GraphicalBoard(std::shared_ptr<NcHandler> ncHandler,
                               ncplane *const PLANE) {
    ncplane_options nopts = extract_nopts(PLANE);
    _rows = nopts.rows + 1;
    _cols = nopts.cols + 1;

    _ncHandler = ncHandler;
    _primaryPlane = PLANE;

    const unsigned int ROWS_PER_BCELL = (_rows - 2) / 3;
    const unsigned int COLS_PER_BCELL = (_cols - 2) / 3;

    for (unsigned int i = 0; i < 9; i++) {
        unsigned int column = i % 3u;
        unsigned int row = (i - column) / 3u;

        int newY = static_cast<int>(1u + (ROWS_PER_BCELL * row));
        int newX = static_cast<int>(1u + (COLS_PER_BCELL * column));

        ncplane_options child_nopts =
            create_nopts(newY, newX, ROWS_PER_BCELL - 1, COLS_PER_BCELL - 1);
        ncplane *tmp = ncplane_create(_primaryPlane, &child_nopts);

        _childPlanes.at(i) = tmp;
    }
}

void GraphicalBoard::draw_board(const std::array<const char *, 3> SYMBOLS,
                                const uint64_t CELL_CHANNELS) {
    const unsigned int ROWS_PER_BCELL = (_rows - 2) / 3u;
    const unsigned int COLS_PER_BCELL = (_cols - 2) / 3u;

    // calculate lines positions and lengths
    const int H_IDX_1 = static_cast<int>(ROWS_PER_BCELL);
    const int H_IDX_2 = static_cast<int>(2u * ROWS_PER_BCELL);

    const int V_IDX_1 = static_cast<int>(COLS_PER_BCELL);
    const int V_IDX_2 = static_cast<int>(2u * COLS_PER_BCELL);

    const unsigned int H_LINE_LEN = (3u * COLS_PER_BCELL) + 1u;
    const unsigned int V_LINE_LEN = (3u * ROWS_PER_BCELL) + 1u;

    // define cells
    nccell HORI_CELL, VERT_CELL, JUNC_CELL;
    HORI_CELL = VERT_CELL = JUNC_CELL = NCCELL_TRIVIAL_INITIALIZER;

    nccell_load(_primaryPlane, &HORI_CELL, SYMBOLS.at(0));
    nccell_load(_primaryPlane, &VERT_CELL, SYMBOLS.at(1));
    nccell_load(_primaryPlane, &JUNC_CELL, SYMBOLS.at(2));
    nccell_set_channels(&HORI_CELL, CELL_CHANNELS);
    nccell_set_channels(&VERT_CELL, CELL_CHANNELS);
    nccell_set_channels(&JUNC_CELL, CELL_CHANNELS);

    // draw horizontal lines
    ncplane_cursor_move_yx(_primaryPlane, H_IDX_1, 0);
    ncplane_hline(_primaryPlane, &HORI_CELL, H_LINE_LEN);

    ncplane_cursor_move_yx(_primaryPlane, H_IDX_2, 0);
    ncplane_hline(_primaryPlane, &HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    ncplane_cursor_move_yx(_primaryPlane, 0, V_IDX_1);
    ncplane_vline(_primaryPlane, &VERT_CELL, V_LINE_LEN);

    ncplane_cursor_move_yx(_primaryPlane, 0, V_IDX_2);
    ncplane_vline(_primaryPlane, &VERT_CELL, V_LINE_LEN);

    // draw junction points
    ncplane_putc_yx(_primaryPlane, H_IDX_1, V_IDX_1, &JUNC_CELL);
    ncplane_putc_yx(_primaryPlane, H_IDX_1, V_IDX_2, &JUNC_CELL);

    ncplane_putc_yx(_primaryPlane, H_IDX_2, V_IDX_1, &JUNC_CELL);
    ncplane_putc_yx(_primaryPlane, H_IDX_2, V_IDX_2, &JUNC_CELL);

    // draw the board to the screen
    _ncHandler->render();
}

void GraphicalBoard::draw_x(const unsigned int INDEX) {
    ncplane *plane = _childPlanes.at(INDEX);
    const nccell red = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    ncplane_erase(plane);
    ncplane_set_base_cell(plane, &red);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::draw_o(const unsigned int INDEX) {
    ncplane *plane = _childPlanes.at(INDEX);
    const nccell blue = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    ncplane_erase(plane);
    ncplane_set_base_cell(plane, &blue);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::fill_x() {
    for (ncplane *const child : _childPlanes) {
        const nccell red = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                        _ncHandler->get_default_fg_channel()));

        ncplane_erase(child);
        ncplane_set_base_cell(child, &red);
    }

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::fill_o() {
    for (ncplane *const child : _childPlanes) {
        const nccell blue = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                        _ncHandler->get_default_fg_channel()));

        ncplane_erase(child);
        ncplane_set_base_cell(child, &blue);
    }

    // update the screen with the new changes
    _ncHandler->render();
}

std::array<ncplane *, 9> GraphicalBoard::get_child_planes() const {
    return _childPlanes;
}
