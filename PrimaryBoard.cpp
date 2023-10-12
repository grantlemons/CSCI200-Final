#include "Shared.h"
#include "Board.h"
#include "PrimaryBoard.h"
#include "LeafBoard.h"

#include <optional>

PrimaryBoard::PrimaryBoard() {
    this->cells = new LeafBoard[9];
}

PrimaryBoard::~PrimaryBoard() {
    delete this->cells;
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    return this->cells[INDEX].winner;
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = &this->cells[INDEX];
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->winner == None ? opt : std::nullopt;
}
