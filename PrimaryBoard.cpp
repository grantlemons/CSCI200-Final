#include "Shared.h"
#include "Board.h"
#include "PrimaryBoard.h"
#include "LeafBoard.h"

#include <optional>
#include <vector>

const char *THICK_SYMBOLS[3] = {"\u2501", "\u2503", "\u254B"};

PrimaryBoard::PrimaryBoard(std::shared_ptr<NcHandler> ncHandler)
    : Board::Board(ncHandler, THICK_SYMBOLS) {
    std::vector<LeafBoard> tmp(9, LeafBoard(ncHandler));
    this->_cells = tmp.data();
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    return this->_cells[INDEX].winner;
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = &this->_cells[INDEX];
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->winner == None ? opt : std::nullopt;
}
