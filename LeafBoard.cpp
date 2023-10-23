#include "Shared.h"
#include "Board.h"
#include "LeafBoard.h"

LeafBoard::LeafBoard() {
    this->_cells = new LLCell[9];
    this->winner = None;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    return (CellOwner)this->_cells[INDEX];
}

// navigation
bool LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    if (this->_cells[INDEX] == None) {
        this->_cells[INDEX] = OWNER;

        if (this->check_win(INDEX, OWNER)) {
            this->winner = OWNER;
        }
        return true;
    }
    return false;
}
