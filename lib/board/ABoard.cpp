/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/board/ABoard.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <cmath>
#include <ostream>

ABoard::ABoard(INcHandler *ncHandler) : _ncHandler{ncHandler} {}

INcHandler *ABoard::getNcHandler() const {
    return _ncHandler;
}

bool ABoard::check_win(const int INDEX, const CELL_OWNER OWNER) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    int horizontalOther1{0}, horizontalOther2{0}, verticalOther1{0},
        verticalOther2{0};

    horizontal_others(INDEX, horizontalOther1, horizontalOther2);
    vertical_others(INDEX, verticalOther1, verticalOther2);

    // set diagonal_other indexes
    // diagonals are only sometimes valid:
    // |0| |2|
    // | |4| |
    // |6| |8|
    bool includeDiagonals2{false};
    bool includeDiagonals4{false};

    int diagonalOther1{0}, diagonalOther2{0};
    int diagonalOther3{0}, diagonalOther4{0};
    if (INDEX == 4) {
        includeDiagonals2 = true;
        includeDiagonals4 = true;
        diagonal_twos_others(INDEX, diagonalOther1, diagonalOther2);
        diagonal_fours_others(INDEX, diagonalOther3, diagonalOther4);
    } else if (INDEX % 4 == 0) {
        includeDiagonals4 = true;
        diagonal_fours_others(INDEX, diagonalOther3, diagonalOther4);
    } else if (INDEX % 2 == 0) {
        includeDiagonals2 = true;
        diagonal_twos_others(INDEX, diagonalOther1, diagonalOther2);
    }
    const bool WON_HORI = get_cell_owner(horizontalOther1) == OWNER &&
                          get_cell_owner(horizontalOther2) == OWNER;
    const bool WON_VERT = get_cell_owner(verticalOther1) == OWNER &&
                          get_cell_owner(verticalOther2) == OWNER;
    const bool WON_DIAGONAL_TWOS = includeDiagonals2 &&
                                   get_cell_owner(diagonalOther1) == OWNER &&
                                   get_cell_owner(diagonalOther2) == OWNER;
    const bool WON_DIAGONALS_FOURS = includeDiagonals4 &&
                                     get_cell_owner(diagonalOther3) == OWNER &&
                                     get_cell_owner(diagonalOther4) == OWNER;

    return get_cell_owner(INDEX) == OWNER &&
           (WON_HORI || WON_VERT || WON_DIAGONAL_TWOS || WON_DIAGONALS_FOURS);
}

void ABoard::mark_cell(const int INDEX, const CELL_OWNER OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);

    switch (OWNER) {
    case X:
        getGraphicalBoard()->draw_x(INDEX);
        break;
    case O:
        getGraphicalBoard()->draw_o(INDEX);
        break;
    case TIE:
        getGraphicalBoard()->draw_tie(INDEX);
        break;
    default:
        break;
    }
}

std::ostream &operator<<(std::ostream &out, const ABoard &BRD) {
    out << "[";
    for (int i = 0; i < gsl::narrow<int>(CELL_COUNT - 1); i++) {
        out << BRD.get_cell_owner(i) << ", ";

        if ((i + 1) % 3 == 0) {
            out << std::endl << " ";
        }
    }
    out << BRD.get_cell_owner(CELL_COUNT) << "]";

    return out;
}
