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
    : Board::Board(
          ncHandler, def_primary_nopts(ncHandler),
          NcHandler::combine_channels(ncHandler->get_default_bg_channel(),
                                      ncHandler->get_default_fg_channel()),
          PrimaryBoard::_symbols) {
    this->_cells = std::array<LeafBoard *, 9>();

    for (int i = 0; i < 9; i++) {
        ncplane *plane = this->mGBoard.get_child_planes().at(i);

        LeafBoard *newBoard = new LeafBoard(ncHandler, plane);
        this->_cells.at(i) = newBoard;
    }
}

PrimaryBoard::~PrimaryBoard() {
    for (LeafBoard *const cell : this->_cells) {
        delete cell;
    }
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    return this->_cells.at(INDEX)->get_winner();
}

void PrimaryBoard::draw_x(const unsigned int INDEX) {
    this->_cells.at(INDEX)->fill_x();
    this->Board::draw_x(INDEX);
}

void PrimaryBoard::draw_o(const unsigned int INDEX) {
    this->_cells.at(INDEX)->fill_o();
    this->Board::draw_o(INDEX);
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = this->_cells.at(INDEX);
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->get_winner() == None ? opt : std::nullopt;
}

ncplane_options def_primary_nopts(std::shared_ptr<NcHandler> ncHandler) {
    ncplane *std = ncHandler->get_stdplane();

    const int ROWS = (3 * 11) + 2;
    const int COLS = (3 * 20) + 2;

    unsigned int std_rows, std_cols;
    ncplane_dim_yx(std, &std_rows, &std_cols);

    unsigned int std_center_y, std_center_x;
    std_center_y = std_rows / 2;
    std_center_x = std_cols / 2;

    int board_origin_y, board_origin_x;
    board_origin_y = std_center_y - (ROWS / 2);
    board_origin_x = std_center_x - (COLS / 2);

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, NULL, NULL, NULL, 0, 0, 0,
    };

    return nopts;
}
