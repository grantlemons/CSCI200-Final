/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/graphical_board/AGraphicalBoard.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <array>
#include <notcurses/notcurses.h>
#include <unistd.h>

AGraphicalBoard::AGraphicalBoard(INcHandler *const P_ncHandler, const int Y,
                                 const int X, const int ROWS, const int COLS)
    : mNcHandler{P_ncHandler},
      mPrimaryPlane{new NcPlaneWrapper{P_ncHandler, Y, X, ROWS, COLS}},
      mRows{ROWS + 1}, mCols{COLS + 1} {
    Expects(ROWS >= 0 && COLS >= 0);
}

AGraphicalBoard::AGraphicalBoard(INcHandler *const P_ncHandler,
                                 const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{
          P_ncHandler, std::make_unique<NcPlaneWrapper>(P_ncHandler, NOPTS)} {}

AGraphicalBoard::AGraphicalBoard(INcHandler *const P_ncHandler,
                                 std::unique_ptr<INcPlaneWrapper> P_plane)
    : mNcHandler{P_ncHandler}, mPrimaryPlane{std::move(P_plane)},
      mRows{mPrimaryPlane->get_rows() + 1},
      mCols{mPrimaryPlane->get_cols() + 1} {
    Expects(mRows >= 0 && mCols >= 0);
}

void AGraphicalBoard::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {
    const int ROWS_PER_BCELL = (mRows - 2) / 3;
    const int COLS_PER_BCELL = (mCols - 2) / 3;

    // calculate lines positions and lengths
    const int H_IDX_1 = ROWS_PER_BCELL;
    const int H_IDX_2 = 2 * ROWS_PER_BCELL;

    const int V_IDX_1 = COLS_PER_BCELL;
    const int V_IDX_2 = 2 * COLS_PER_BCELL;

    const auto H_LINE_LEN = gsl::narrow<unsigned int>((3 * COLS_PER_BCELL) + 1);
    const auto V_LINE_LEN = gsl::narrow<unsigned int>((3 * ROWS_PER_BCELL) + 1);

    // define cells
    nccell horiCell, vertCell, juncCell;
    horiCell = vertCell = juncCell = NCCELL_TRIVIAL_INITIALIZER;

    mPrimaryPlane->load_nccell(&horiCell, SYMBOLS.at(0));
    mPrimaryPlane->load_nccell(&vertCell, SYMBOLS.at(1));
    mPrimaryPlane->load_nccell(&juncCell, SYMBOLS.at(2));
    nccell_set_channels(&horiCell, CELL_CHANNELS);
    nccell_set_channels(&vertCell, CELL_CHANNELS);
    nccell_set_channels(&juncCell, CELL_CHANNELS);

    // draw horizontal lines
    mPrimaryPlane->cursor_move_yx(H_IDX_1, 0);
    mPrimaryPlane->hline(&horiCell, H_LINE_LEN);

    mPrimaryPlane->cursor_move_yx(H_IDX_2, 0);
    mPrimaryPlane->hline(&horiCell, H_LINE_LEN);

    // draw vertical lines
    mPrimaryPlane->cursor_move_yx(0, V_IDX_1);
    mPrimaryPlane->vline(&vertCell, V_LINE_LEN);

    mPrimaryPlane->cursor_move_yx(0, V_IDX_2);
    mPrimaryPlane->vline(&vertCell, V_LINE_LEN);

    // draw junction points
    mPrimaryPlane->putc_yx(H_IDX_1, V_IDX_1, &juncCell);
    mPrimaryPlane->putc_yx(H_IDX_1, V_IDX_2, &juncCell);

    mPrimaryPlane->putc_yx(H_IDX_2, V_IDX_1, &juncCell);
    mPrimaryPlane->putc_yx(H_IDX_2, V_IDX_2, &juncCell);

    // draw the board to the screen
    mNcHandler->render();
}

void AGraphicalBoard::draw_x(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    IGraphicalArea *const P_plane =
        mChildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell RED = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                   mNcHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&RED);

    // update the screen with the new changes
    mNcHandler->render();
}

void AGraphicalBoard::draw_o(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    IGraphicalArea *const P_plane =
        mChildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell BLUE = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combineChannels(NcHandler::BLUE_CHANNEL,
                                   mNcHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&BLUE);

    // update the screen with the new changes
    mNcHandler->render();
}

void AGraphicalBoard::draw_tie(const int INDEX) {
    IGraphicalArea *const P_plane =
        mChildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell GREY = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combineChannels(NcHandler::GREY_CHANNEL,
                                   mNcHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&GREY);

    // update the screen with the new changes
    mNcHandler->render();
}

std::array<IGraphicalArea *, CELL_COUNT> AGraphicalBoard::get_children() {
    std::array<IGraphicalArea *, CELL_COUNT> arr{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        arr.at(i) = mChildren.at(i).get();
    }

    return arr;
}

// Inherited methods of INcPlaneWrapper
void AGraphicalBoard::dim_yx(int &ROWS, int &COLS) const {
    mPrimaryPlane->dim_yx(ROWS, COLS);
}
int AGraphicalBoard::get_rows() const {
    return mPrimaryPlane->get_rows();
}
int AGraphicalBoard::get_cols() const {
    return mPrimaryPlane->get_cols();
}

IGraphicalArea *AGraphicalBoard::create_child(const ncplane_options *nopts) {
    return mPrimaryPlane->create_child(nopts);
}

int AGraphicalBoard::load_nccell(nccell *const P_c, const char *gcluster) {
    return mPrimaryPlane->load_nccell(P_c, gcluster);
}
int AGraphicalBoard::set_base_cell(const nccell *const P_c) {
    return mPrimaryPlane->set_base_cell(P_c);
}

int AGraphicalBoard::cursor_move_yx(const int X, const int Y) {
    return mPrimaryPlane->cursor_move_yx(X, Y);
}
int AGraphicalBoard::hline(const nccell *const P_c, const unsigned LEN) {
    return mPrimaryPlane->hline(P_c, LEN);
}
int AGraphicalBoard::vline(const nccell *const P_c, const unsigned LEN) {
    return mPrimaryPlane->vline(P_c, LEN);
}
int AGraphicalBoard::putc_yx(const int Y, const int X,
                             const nccell *const P_c) {
    return mPrimaryPlane->putc_yx(Y, X, P_c);
}
void AGraphicalBoard::erase() {
    mPrimaryPlane->erase();

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        mChildren.at(i)->erase();
    }
}
