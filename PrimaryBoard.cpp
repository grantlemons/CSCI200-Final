#include "Shared.h"
#include "Board.h"
#include "PrimaryBoard.h"
#include "LeafBoard.h"

#include <optional>

PrimaryBoard::PrimaryBoard() {
    this->_cells = new LeafBoard[9];
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    return this->_cells[INDEX].winner;
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = &this->_cells[INDEX];
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->winner == None ? opt : std::nullopt;
}
