#include "lib/graphical_board/GraphicalBoardA.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <array>
#include <notcurses/notcurses.h>
#include <unistd.h>

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const P_ncHandler, int const Y,
                                 int const X, int const ROWS, int const COLS)
    : mncHandler{P_ncHandler},
      mprimaryPlane{new NcPlaneWrapper{P_ncHandler, Y, X, ROWS, COLS}},
      mrows{ROWS + 1}, mcols{COLS + 1} {
    Expects(ROWS >= 0 && COLS >= 0);
}

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const P_ncHandler,
                                 ncplane_options const NOPTS)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler,
                                       new NcPlaneWrapper(P_ncHandler, NOPTS)} {
}

GraphicalBoardA::GraphicalBoardA(NcHandlerI *const P_ncHandler,
                                 NcPlaneWrapperI *const P_plane)
    : mncHandler{P_ncHandler}, mprimaryPlane{P_plane},
      mrows{mprimaryPlane->get_rows() + 1},
      mcols{mprimaryPlane->get_cols() + 1} {
    Expects(mrows >= 0 && mcols >= 0);
}

void GraphicalBoardA::draw_board(
    std::array<char const *, SYMBOL_COUNT> const SYMBOLS,
    uint64_t const CELL_CHANNELS) {
    int const ROWS_PER_BCELL = (mrows - 2) / 3;
    int const COLS_PER_BCELL = (mcols - 2) / 3;

    // calculate lines positions and lengths
    int const H_IDX_1 = ROWS_PER_BCELL;
    int const H_IDX_2 = 2 * ROWS_PER_BCELL;

    int const V_IDX_1 = COLS_PER_BCELL;
    int const V_IDX_2 = 2 * COLS_PER_BCELL;

    auto const H_LINE_LEN = gsl::narrow<unsigned int>((3 * COLS_PER_BCELL) + 1);
    auto const V_LINE_LEN = gsl::narrow<unsigned int>((3 * ROWS_PER_BCELL) + 1);

    // define cells
    nccell horiCell, vertCell, juncCell;
    horiCell = vertCell = juncCell = NCCELL_TRIVIAL_INITIALIZER;

    mprimaryPlane->load_nccell(&horiCell, SYMBOLS.at(0));
    mprimaryPlane->load_nccell(&vertCell, SYMBOLS.at(1));
    mprimaryPlane->load_nccell(&juncCell, SYMBOLS.at(2));
    nccell_set_channels(&horiCell, CELL_CHANNELS);
    nccell_set_channels(&vertCell, CELL_CHANNELS);
    nccell_set_channels(&juncCell, CELL_CHANNELS);

    // draw horizontal lines
    mprimaryPlane->cursor_move_yx(H_IDX_1, 0);
    mprimaryPlane->hline(&horiCell, H_LINE_LEN);

    mprimaryPlane->cursor_move_yx(H_IDX_2, 0);
    mprimaryPlane->hline(&horiCell, H_LINE_LEN);

    // draw vertical lines
    mprimaryPlane->cursor_move_yx(0, V_IDX_1);
    mprimaryPlane->vline(&vertCell, V_LINE_LEN);

    mprimaryPlane->cursor_move_yx(0, V_IDX_2);
    mprimaryPlane->vline(&vertCell, V_LINE_LEN);

    // draw junction points
    mprimaryPlane->putc_yx(H_IDX_1, V_IDX_1, &juncCell);
    mprimaryPlane->putc_yx(H_IDX_1, V_IDX_2, &juncCell);

    mprimaryPlane->putc_yx(H_IDX_2, V_IDX_1, &juncCell);
    mprimaryPlane->putc_yx(H_IDX_2, V_IDX_2, &juncCell);

    // draw the board to the screen
    mncHandler->render();
}

void GraphicalBoardA::draw_x(int const INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    GraphicalAreaI *const P_plane =
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    nccell const RED = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                    mncHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&RED);

    // update the screen with the new changes
    mncHandler->render();
}

void GraphicalBoardA::draw_o(int const INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    GraphicalAreaI *const P_plane =
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    nccell const BLUE = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combine_channels(NcHandler::BLUE_CHANNEL,
                                    mncHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&BLUE);

    // update the screen with the new changes
    mncHandler->render();
}

std::array<GraphicalAreaI *, CELL_COUNT> GraphicalBoardA::get_children() {
    std::array<GraphicalAreaI *, CELL_COUNT> arr{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        arr.at(i) = mchildren.at(i).get();
    }

    return arr;
}

// Inherited methods of NcPlaneWrapperI
void GraphicalBoardA::dim_yx(int &ROWS, int &COLS) const {
    mprimaryPlane->dim_yx(ROWS, COLS);
}
int GraphicalBoardA::get_rows() const {
    return mprimaryPlane->get_rows();
}
int GraphicalBoardA::get_cols() const {
    return mprimaryPlane->get_cols();
}

GraphicalAreaI *GraphicalBoardA::create_child(ncplane_options const *nopts) {
    return mprimaryPlane->create_child(nopts);
}

int GraphicalBoardA::load_nccell(nccell *const P_c, char const *gcluster) {
    return mprimaryPlane->load_nccell(P_c, gcluster);
}
int GraphicalBoardA::set_base_cell(nccell const *const P_c) {
    return mprimaryPlane->set_base_cell(P_c);
}

int GraphicalBoardA::cursor_move_yx(int const X, int const Y) {
    return mprimaryPlane->cursor_move_yx(X, Y);
}
int GraphicalBoardA::hline(nccell const *const P_c, unsigned const LEN) {
    return mprimaryPlane->hline(P_c, LEN);
}
int GraphicalBoardA::vline(nccell const *const P_c, unsigned const LEN) {
    return mprimaryPlane->vline(P_c, LEN);
}
int GraphicalBoardA::putc_yx(int const Y, int const X,
                             nccell const *const P_c) {
    return mprimaryPlane->putc_yx(Y, X, P_c);
}
void GraphicalBoardA::erase() {
    mprimaryPlane->erase();

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        mchildren.at(i)->erase();
    }
}
