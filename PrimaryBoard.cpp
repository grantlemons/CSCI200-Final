#include "Shared.h"
#include "Board.h"
#include "PrimaryBoard.h"
#include "LeafBoard.h"

#include <optional>

PrimaryBoard::PrimaryBoard() : Board() {
    this->cells = new LeafBoard[9];
}

PrimaryBoard::~PrimaryBoard() {
    delete this->cells;
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = &this->cells[INDEX];
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->winner == None ? opt : std::nullopt;
}

bool PrimaryBoard::check_win(const int INDEX, const CellOwner OWNER) const {
    int horizontal_other1, horizontal_other2;
    int vertical_other1, vertical_other2;

    horizontal_others(INDEX, horizontal_other1, horizontal_other2);
    vertical_others(INDEX, vertical_other1, vertical_other2);

    // set diagonal_other indexes
    // diagonals are only sometimes valid:
    // |0| |2|
    // | |4| |
    // |6| |8|
    bool include_diagonals2 = true;
    bool include_diagonals4 = true;
    int diagonal_other1, diagonal_other2;
    int diagonal_other3, diagonal_other4;
    if (INDEX % 2 != 0) {
        include_diagonals2 = false;
        include_diagonals4 = false;
    } else if (INDEX == 4) {
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 4) {
        include_diagonals2 = false;
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else {
        include_diagonals4 = false;
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
    }

    return this->cells[INDEX].winner == OWNER &&
           ((this->cells[horizontal_other1].winner == OWNER &&
             this->cells[horizontal_other2].winner == OWNER) ||
            (this->cells[vertical_other1].winner == OWNER &&
             this->cells[vertical_other2].winner == OWNER) ||
            (include_diagonals2 &&
             this->cells[diagonal_other1].winner == OWNER &&
             this->cells[diagonal_other2].winner == OWNER) ||
            (include_diagonals4 &&
             this->cells[diagonal_other3].winner == OWNER &&
             this->cells[diagonal_other4].winner == OWNER));
}
