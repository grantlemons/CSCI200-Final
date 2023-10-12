#include "Board.h"
#include "Shared.h"

#include <ostream>

// check victory
bool Board::check_win(const int INDEX, const CellOwner OWNER) const {
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

    return get_cell_owner(INDEX) == OWNER &&
           ((get_cell_owner(horizontal_other1) == OWNER &&
             get_cell_owner(horizontal_other2) == OWNER) ||
            (get_cell_owner(vertical_other1) == OWNER &&
             get_cell_owner(vertical_other2) == OWNER) ||
            (include_diagonals2 && get_cell_owner(diagonal_other1) == OWNER &&
             get_cell_owner(diagonal_other2) == OWNER) ||
            (include_diagonals4 && get_cell_owner(diagonal_other3) == OWNER &&
             get_cell_owner(diagonal_other4) == OWNER));
}

std::ostream &operator<<(std::ostream &out, const Board &BRD) {
    out << "[";
    for (int i = 0; i < 9 - 1; i++) {
        out << BRD.get_cell_owner(i) << ", ";

        if ((i + 1) % 3 == 0) {
            out << std::endl << " ";
        }
    }
    out << BRD.get_cell_owner(8) << "]";

    return out;
}
