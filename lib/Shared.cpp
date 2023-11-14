#include "lib/Shared.h"

#include <ostream>

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER) {
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
        out << "Unknown CellOwner Variant";
    }
    return out;
}
