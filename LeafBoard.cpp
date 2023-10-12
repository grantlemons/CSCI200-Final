#include "Shared.h"
#include "Board.h"
#include "LeafBoard.h"

LeafBoard::LeafBoard() {
    this->cells = new LLCell[9];
    this->winner = None;
}

LeafBoard::~LeafBoard() {
    delete this->cells;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    return (CellOwner)this->cells[INDEX];
}

// navigation
bool LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    if (this->cells[INDEX] == None) {
        this->cells[INDEX] = OWNER;

        if (this->check_win(INDEX, OWNER)) {
            this->winner = OWNER;
        }
        return true;
    }
    return false;
}
