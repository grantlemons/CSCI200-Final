#include "lib/board/Board.h"

#include "lib/GraphicalBoard.h"
#include "lib/NcHandler.h"
#include "lib/Shared.h"

#include <array>
#include <cmath>
#include <memory>
#include <notcurses/notcurses.h>
#include <ostream>

Board::Board(std::shared_ptr<NcHandler> ncHandler, ncplane *PLANE,
             const uint64_t CELL_CHANNELS, std::array<const char *, 3> SYMBOLS)
    : mGBoard(ncHandler, PLANE, CELL_CHANNELS, SYMBOLS) {
    draw();
}

Board::Board(std::shared_ptr<NcHandler> ncHandler, const ncplane_options NOPTS,
             const uint64_t CELL_CHANNELS, std::array<const char *, 3> SYMBOLS)
    : mGBoard(ncHandler, NOPTS, CELL_CHANNELS, SYMBOLS) {
    draw();
}

unsigned int negative_mod(const int A, const int B) {
    return static_cast<unsigned int>(
        A - (B * static_cast<int>(floor(static_cast<double>(A) / B))));
}

void horizontal_others(const unsigned int INDEX, unsigned int &other1,
                       unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 1u), 3u);
    other2 = (INDEX + 1u) % 3u;
}
void vertical_others(const unsigned int INDEX, unsigned int &other1,
                     unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 3u), 9u);
    other2 = (INDEX + 3u) % 9u;
}
void diagonal_fours_others(const unsigned int INDEX, unsigned int &other1,
                           unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 4u), 12u);
    other2 = (INDEX + 4u) % 12u;
}
void diagonal_twos_others(const unsigned int INDEX, unsigned int &other1,
                          unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 2u), 10u);
    other2 = (INDEX + 2u) % 10u;
}

bool Board::check_win(const unsigned int INDEX, const CellOwner OWNER) const {
    unsigned int horizontal_other1, horizontal_other2, vertical_other1,
        vertical_other2;

    horizontal_others(INDEX, horizontal_other1, horizontal_other2);
    vertical_others(INDEX, vertical_other1, vertical_other2);

    // set diagonal_other indexes
    // diagonals are only sometimes valid:
    // |0| |2|
    // | |4| |
    // |6| |8|
    bool include_diagonals2 = false;
    bool include_diagonals4 = false;
    unsigned int diagonal_other1 = 0, diagonal_other2 = 0;
    unsigned int diagonal_other3 = 0, diagonal_other4 = 0;
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

    const bool WON_HORI = get_cell_owner(horizontal_other1) == OWNER &&
                          get_cell_owner(horizontal_other2) == OWNER;
    const bool WON_VERT = get_cell_owner(vertical_other1) == OWNER &&
                          get_cell_owner(vertical_other2) == OWNER;
    const bool WON_DIAGONAL_TWOS = include_diagonals2 &&
                                   get_cell_owner(diagonal_other1) == OWNER &&
                                   get_cell_owner(diagonal_other2) == OWNER;
    const bool WON_DIAGONALS_FOURS = include_diagonals4 &&
                                     get_cell_owner(diagonal_other3) == OWNER &&
                                     get_cell_owner(diagonal_other4) == OWNER;

    return WON_HORI || WON_VERT || WON_DIAGONAL_TWOS || WON_DIAGONALS_FOURS;
}

void Board::draw() {
    mGBoard.draw_board();
}
void Board::draw_x(const unsigned int INDEX) {
    mGBoard.draw_x(INDEX);
}
void Board::draw_o(const unsigned int INDEX) {
    mGBoard.draw_o(INDEX);
}

std::ostream &operator<<(std::ostream &out, const Board &BRD) {
    out << "[";
    for (unsigned int i = 0; i < 9 - 1; i++) {
        out << BRD.get_cell_owner(i) << ", ";

        if ((i + 1) % 3 == 0) {
            out << std::endl << " ";
        }
    }
    out << BRD.get_cell_owner(8) << "]";

    return out;
}
