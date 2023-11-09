#include "lib/board/PrimaryBoard.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>
#include <optional>

std::array<const char *, 3> PrimaryBoard::_symbols =
    std::array<const char *, 3>({"\u2501", "\u2503", "\u254B"});

PrimaryBoard::PrimaryBoard(std::shared_ptr<NcHandler> ncHandler)
    : Board::Board(ncHandler, def_primary_nopts(ncHandler),
                   ncHandler->get_default_channels(), PrimaryBoard::_symbols) {
    _cells = std::array<LeafBoard *, 9>();

    for (unsigned int i = 0; i < 9; i++) {
        ncplane *plane = mGBoard.get_child_planes().at(i);

        LeafBoard *newBoard = new LeafBoard(ncHandler, plane);
        _cells.at(i) = newBoard;
    }
}

PrimaryBoard::~PrimaryBoard() {
    for (LeafBoard *const cell : _cells) {
        delete cell;
    }
}

CellOwner PrimaryBoard::get_cell_owner(const unsigned int INDEX) const {
    return _cells.at(INDEX)->get_winner();
}

void PrimaryBoard::draw_x(const unsigned int INDEX) {
    _cells.at(INDEX)->fill_x();
    Board::draw_x(INDEX);
}

void PrimaryBoard::draw_o(const unsigned int INDEX) {
    _cells.at(INDEX)->fill_o();
    this->Board::draw_o(INDEX);
}

std::optional<LeafBoard *>
PrimaryBoard::select_board(const unsigned int INDEX) const {
    LeafBoard *cell = _cells.at(INDEX);
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->get_winner() == None ? opt : std::nullopt;
}

ncplane_options def_primary_nopts(std::shared_ptr<NcHandler> ncHandler) {
    ncplane *std = ncHandler->get_stdplane();

    const unsigned int ROWS = (3u * 11u) + 2u;
    const unsigned int COLS = (3u * 20u) + 2u;

    unsigned int std_rows, std_cols;
    ncplane_dim_yx(std, &std_rows, &std_cols);

    unsigned int std_center_y, std_center_x;
    std_center_y = std_rows / 2u;
    std_center_x = std_cols / 2u;

    int board_origin_y, board_origin_x;
    board_origin_y = static_cast<int>(std_center_y - (ROWS / 2u));
    board_origin_x = static_cast<int>(std_center_x - (COLS / 2u));

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };

    return nopts;
}
