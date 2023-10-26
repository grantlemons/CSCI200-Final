#include "lib/board/Board.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/GraphicalBoard.h"

#include <cmath>
#include <memory>
#include <notcurses/notcurses.h>
#include <ostream>

Board::Board(std::shared_ptr<NcHandler> ncHandler, ncplane *PLANE,
             const uint64_t CELL_CHANNELS, const char **const SYMBOLS)
    : _gboard(ncHandler, PLANE, CELL_CHANNELS, SYMBOLS) {
    this->draw();
}

Board::Board(std::shared_ptr<NcHandler> ncHandler, const ncplane_options NOPTS,
             const uint64_t CELL_CHANNELS, const char **const SYMBOLS)
    : _gboard(ncHandler, NOPTS, CELL_CHANNELS, SYMBOLS) {
    this->draw();
}

unsigned int negative_mod(int a, int b) {
    return a - (b * floor((double)a / b));
}

void horizontal_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 1, 3);
    other2 = (INDEX + 1) % 3;
}
void vertical_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 3, 9);
    other2 = (INDEX + 3) % 9;
}
void diagonal_fours_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 4, 12);
    other2 = (INDEX + 4) % 12;
}
void diagonal_twos_others(const int INDEX, int &other1, int &other2) {
    other1 = negative_mod(INDEX - 2, 10);
    other2 = (INDEX + 2) % 10;
}

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
    bool include_diagonals2 = false;
    bool include_diagonals4 = false;
    int diagonal_other1 = 0, diagonal_other2 = 0;
    int diagonal_other3 = 0, diagonal_other4 = 0;
    if (INDEX == 4) {
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 4) {
        include_diagonals4 = true;
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 2 == 0) {
        include_diagonals2 = true;
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

void Board::draw() {
    this->_gboard.draw_board();
}
// void Board::draw_x(const unsigned int INDEX) {
//     this->_gboard.draw_x(INDEX);
// }
// void Board::draw_o(const unsigned int INDEX) {
//     this->_gboard.draw_o(INDEX);
// }

GraphicalBoard *Board::get_gboard() {
    return &(this->_gboard);
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
