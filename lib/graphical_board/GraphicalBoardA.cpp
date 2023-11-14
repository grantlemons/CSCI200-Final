#include "lib/graphical_board/GraphicalBoardA.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>
#include <unistd.h>

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const ncHandler, const int Y,
                                 const int X, const int ROWS, const int COLS)
    : _primaryPlane{new NcPlaneWrapper{ncHandler, Y, X, ROWS, COLS}},
      _rows{ROWS + 1}, _cols{COLS + 1} {
    Expects(ROWS >= 0 && COLS >= 0);
}

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const ncHandler,
                                 const ncplane_options NOPTS)
    : GraphicalBoardA::GraphicalBoardA{ncHandler,
                                       new NcPlaneWrapper(ncHandler, NOPTS)} {}

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const ncHandler,
                                 NcPlaneWrapperI *const PLANE)
    : _ncHandler{ncHandler}, _primaryPlane{PLANE},
      _rows{_primaryPlane->get_rows() + 1},
      _cols{_primaryPlane->get_cols() + 1} {
    Expects(_rows >= 0 && _cols >= 0);
}

void GraphicalBoardA::draw_board(
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

void GraphicalBoardA::draw_x(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    GraphicalAreaI *const PLANE =
        _children.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell red = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    PLANE->erase();
    PLANE->set_base_cell(&red);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoardA::draw_o(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    GraphicalAreaI *const PLANE =
        _children.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell blue = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                    _ncHandler->get_default_fg_channel()));

    PLANE->erase();
    PLANE->set_base_cell(&blue);

    // update the screen with the new changes
    _ncHandler->render();
}

void GraphicalBoardA::fill_x() {
    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        GraphicalAreaI *const CHILD = _children.at(i).get();
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

void GraphicalBoardA::fill_o() {
    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        GraphicalAreaI *const CHILD = _children.at(i).get();
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

std::array<GraphicalAreaI *, CELL_COUNT> GraphicalBoardA::get_children() {
    std::array<GraphicalAreaI *, CELL_COUNT> arr{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        arr.at(i) = _children.at(i).get();
    }

    return arr;
}

// Inherited methods of NcPlaneWrapperI
void GraphicalBoardA::dim_yx(int &ROWS, int &COLS) const {
    _primaryPlane->dim_yx(ROWS, COLS);
}
int GraphicalBoardA::get_rows() const {
    return _primaryPlane->get_rows();
}
int GraphicalBoardA::get_cols() const {
    return _primaryPlane->get_cols();
}

GraphicalAreaI *GraphicalBoardA::create_child(const ncplane_options *nopts) {
    return _primaryPlane->create_child(nopts);
}

int GraphicalBoardA::load_nccell(nccell *const c, const char *gcluster) {
    return _primaryPlane->load_nccell(c, gcluster);
}
int GraphicalBoardA::set_base_cell(const nccell *const c) {
    return _primaryPlane->set_base_cell(c);
}

int GraphicalBoardA::cursor_move_yx(const int X, const int Y) {
    return _primaryPlane->cursor_move_yx(X, Y);
}
int GraphicalBoardA::hline(const nccell *const c, const unsigned LEN) {
    return _primaryPlane->hline(c, LEN);
}
int GraphicalBoardA::vline(const nccell *const c, const unsigned LEN) {
    return _primaryPlane->vline(c, LEN);
}
int GraphicalBoardA::putc_yx(const int Y, const int X, const nccell *const c) {
    return _primaryPlane->putc_yx(Y, X, c);
}
void GraphicalBoardA::erase() {
    _primaryPlane->erase();

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        _children.at(i)->erase();
    }
}
