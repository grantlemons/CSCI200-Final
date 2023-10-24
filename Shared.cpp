#include <ostream>

#include "Shared.h"

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER) {
    if (OWNER == None) {
        return out << "N";
    } else if (OWNER == Player1) {
        return out << "1";
    } else if (OWNER == Player2) {
        return out << "2";
    } else {
        return out << "Unknown CellOwner Variant";
    }
}
