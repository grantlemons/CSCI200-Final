#include "Shared.h"
#include "Board.h"
#include "LeafBoard.h"
#include <iostream>

LeafBoard::LeafBoard() : Board() {
    this->cells = new LLCell[9];
}

LeafBoard::~LeafBoard() {
    delete this->cells;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    return (CellOwner)this->cells[INDEX];
}

// navigation
void LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    if (this->cells[INDEX] == None) {
        this->cells[INDEX] = OWNER;

        if (this->check_win(INDEX, OWNER)) {
            this->winner = OWNER;
        }
    }
}
