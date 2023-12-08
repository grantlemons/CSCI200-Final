/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/Shared.h"

#include <ostream>

std::ostream &operator<<(std::ostream &out, const CELL_OWNER OWNER) {
    switch (OWNER) {
    case NONE:
        out << "N";
        break;
    case X:
        out << "X";
        break;
    case O:
        out << "O";
        break;
    default:
        out << "Unknown CELL_OWNER Variant";
    }
    return out;
}

CELL_OWNER get_other_player(const CELL_OWNER PLAYER) {
    if (PLAYER == X) {
        return O;
    } else if (PLAYER == O) {
        return X;
    } else {
        throw;
    }
}
