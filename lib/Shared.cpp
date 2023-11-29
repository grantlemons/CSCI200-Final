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
