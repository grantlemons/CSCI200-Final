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
    : mncHandler{P_ncHandler},
      mprimaryPlane{new NcPlaneWrapper{P_ncHandler, Y, X, ROWS, COLS}},
      mrows{ROWS + 1}, mcols{COLS + 1} {
    Expects(ROWS >= 0 && COLS >= 0);
}

AGraphicalBoard::AGraphicalBoard(INcHandler *const P_ncHandler,
                                 const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{
          P_ncHandler, std::make_unique<NcPlaneWrapper>(P_ncHandler, NOPTS)} {}

AGraphicalBoard::AGraphicalBoard(INcHandler *const P_ncHandler,
                                 std::unique_ptr<INcPlaneWrapper> P_plane)
    : mncHandler{P_ncHandler}, mprimaryPlane{std::move(P_plane)},
      mrows{mprimaryPlane->get_rows() + 1},
      mcols{mprimaryPlane->get_cols() + 1} {
    Expects(mrows >= 0 && mcols >= 0);
}

void AGraphicalBoard::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {
    const int ROWS_PER_BCELL = (mrows - 2) / 3;
    const int COLS_PER_BCELL = (mcols - 2) / 3;

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

void AGraphicalBoard::draw_x(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    IGraphicalArea *const P_plane =
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell RED = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                   mncHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&RED);

    // update the screen with the new changes
    mncHandler->render();
}

void AGraphicalBoard::draw_o(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    IGraphicalArea *const P_plane =
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get();
    const nccell BLUE = NCCELL_INITIALIZER(
        '\0', 0,
        NcHandler::combineChannels(NcHandler::BLUE_CHANNEL,
                                   mncHandler->get_default_fg_channel()));

    P_plane->erase();
    P_plane->set_base_cell(&BLUE);

    // update the screen with the new changes
    mncHandler->render();
}

std::array<IGraphicalArea *, CELL_COUNT> AGraphicalBoard::get_children() {
    std::array<IGraphicalArea *, CELL_COUNT> arr{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        arr.at(i) = mchildren.at(i).get();
    }

    return arr;
}

// Inherited methods of INcPlaneWrapper
void AGraphicalBoard::dim_yx(int &ROWS, int &COLS) const {
    mprimaryPlane->dim_yx(ROWS, COLS);
}
int AGraphicalBoard::get_rows() const {
    return mprimaryPlane->get_rows();
}
int AGraphicalBoard::get_cols() const {
    return mprimaryPlane->get_cols();
}

IGraphicalArea *AGraphicalBoard::create_child(const ncplane_options *nopts) {
    return mprimaryPlane->create_child(nopts);
}

int AGraphicalBoard::load_nccell(nccell *const P_c, const char *gcluster) {
    return mprimaryPlane->load_nccell(P_c, gcluster);
}
int AGraphicalBoard::set_base_cell(const nccell *const P_c) {
    return mprimaryPlane->set_base_cell(P_c);
}

int AGraphicalBoard::cursor_move_yx(const int X, const int Y) {
    return mprimaryPlane->cursor_move_yx(X, Y);
}
int AGraphicalBoard::hline(const nccell *const P_c, const unsigned LEN) {
    return mprimaryPlane->hline(P_c, LEN);
}
int AGraphicalBoard::vline(const nccell *const P_c, const unsigned LEN) {
    return mprimaryPlane->vline(P_c, LEN);
}
int AGraphicalBoard::putc_yx(const int Y, const int X,
                             const nccell *const P_c) {
    return mprimaryPlane->putc_yx(Y, X, P_c);
}
void AGraphicalBoard::erase() {
    mprimaryPlane->erase();

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        mchildren.at(i)->erase();
    }
}
