#include "lib/GraphicalBoard.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>
#include <unistd.h>

GraphicalBoard::GraphicalBoard(NcHandlerI *ncHandler, const int Y, const int X,
                               const int ROWS, const int COLS)
    : _primaryPlane(new NcPlaneWrapper(ncHandler, Y, X, ROWS, COLS)),
      _rows{ROWS + 1}, _cols{COLS + 1} {
    Expects(ROWS >= 0 && COLS >= 0);

    init_child_planes();
}

GraphicalBoard::GraphicalBoard(NcHandlerI *ncHandler,
                               const ncplane_options NOPTS)
    : GraphicalBoard::GraphicalBoard(
          ncHandler, std::unique_ptr<NcPlaneWrapperI>(
                         new NcPlaneWrapper(ncHandler, NOPTS))) {}

GraphicalBoard::GraphicalBoard(NcHandlerI *ncHandler,
                               std::unique_ptr<NcPlaneWrapperI> plane)
    : _ncHandler{ncHandler}, _primaryPlane{std::move(plane)},
      _rows{_primaryPlane->get_rows() + 1},
      _cols{_primaryPlane->get_cols() + 1} {
    Expects(_rows >= 0 && _cols >= 0);

    init_child_planes();
}

void GraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(_rows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(_cols) - 2u) / 3u;

    for (unsigned int i = 0; i < 9; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options child_nopts =
            create_nopts(newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        NcPlaneWrapperI *tmp = _primaryPlane->create_child(&child_nopts);

        _childPlanes.at(i) = tmp;
    }
}

void GraphicalBoard::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {
    const int ROWS_PER_BCELL = (_rows - 2) / 3;
    const int COLS_PER_BCELL = (_cols - 2) / 3;

    // calculate lines positions and lengths
    const int H_IDX_1 = ROWS_PER_BCELL;
    const int H_IDX_2 = 2 * ROWS_PER_BCELL;

    const int V_IDX_1 = COLS_PER_BCELL;
    const int V_IDX_2 = 2 * COLS_PER_BCELL;

    const unsigned int H_LINE_LEN =
        gsl::narrow<unsigned int>((3 * COLS_PER_BCELL) + 1);
    const unsigned int V_LINE_LEN =
        gsl::narrow<unsigned int>((3 * ROWS_PER_BCELL) + 1);

    // define cells
    nccell HORI_CELL, VERT_CELL, JUNC_CELL;
    HORI_CELL = VERT_CELL = JUNC_CELL = NCCELL_TRIVIAL_INITIALIZER;

    _primaryPlane->load_nccell(&HORI_CELL, SYMBOLS.at(0));
    _primaryPlane->load_nccell(&VERT_CELL, SYMBOLS.at(1));
    _primaryPlane->load_nccell(&JUNC_CELL, SYMBOLS.at(2));
    nccell_set_channels(&HORI_CELL, CELL_CHANNELS);
    nccell_set_channels(&VERT_CELL, CELL_CHANNELS);
    nccell_set_channels(&JUNC_CELL, CELL_CHANNELS);

    // draw horizontal lines
    _primaryPlane->cursor_move_yx(H_IDX_1, 0);
    _primaryPlane->hline(&HORI_CELL, H_LINE_LEN);

    _primaryPlane->cursor_move_yx(H_IDX_2, 0);
    _primaryPlane->hline(&HORI_CELL, H_LINE_LEN);

    // draw vertical lines
    _primaryPlane->cursor_move_yx(0, V_IDX_1);
    _primaryPlane->vline(&VERT_CELL, V_LINE_LEN);

    _primaryPlane->cursor_move_yx(0, V_IDX_2);
    _primaryPlane->vline(&VERT_CELL, V_LINE_LEN);

    // draw junction points
    _primaryPlane->putc_yx(H_IDX_1, V_IDX_1, &JUNC_CELL);
    _primaryPlane->putc_yx(H_IDX_1, V_IDX_2, &JUNC_CELL);

    _primaryPlane->putc_yx(H_IDX_2, V_IDX_1, &JUNC_CELL);
    _primaryPlane->putc_yx(H_IDX_2, V_IDX_2, &JUNC_CELL);

    // draw the board to the screen
    _ncHandler->render();
}

void GraphicalBoard::draw_x(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    NcPlaneWrapperI *const PLANE =
        _childPlanes.at(gsl::narrow<unsigned int>(INDEX));
    const nccell red = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    PLANE->erase();
    PLANE->set_base_cell(&red);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::draw_o(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    NcPlaneWrapperI *const PLANE =
        _childPlanes.at(gsl::narrow<unsigned int>(INDEX));
    const nccell blue = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    PLANE->erase();
    PLANE->set_base_cell(&blue);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::fill_x() {
    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        NcPlaneWrapperI *const CHILD = _childPlanes.at(i);
        const nccell red = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                        _ncHandler->get_default_fg_channel()));

        CHILD->erase();
        CHILD->set_base_cell(&red);
    }

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoard::fill_o() {
    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        NcPlaneWrapperI *const CHILD = _childPlanes.at(i);
        const nccell blue = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                        _ncHandler->get_default_fg_channel()));

        CHILD->erase();
        CHILD->set_base_cell(&blue);
    }

    // update the screen with the new changes
    _ncHandler->render();
}

std::array<NcPlaneWrapperI *, CELL_COUNT> *GraphicalBoard::get_child_planes() {
    return &_childPlanes;
}

std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
GraphicalBoard::create_child_boards() const {
    std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT> boards;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        NcPlaneWrapperI *const PLANE = _childPlanes.at(i);

        boards.at(i) = std::unique_ptr<GraphicalBoardI>(new GraphicalBoard(
            _ncHandler, std::unique_ptr<NcPlaneWrapperI>(PLANE)));
    }

    return boards;
}
