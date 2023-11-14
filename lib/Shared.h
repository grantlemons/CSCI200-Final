#ifndef SHARED
#define SHARED

#include <ostream>

/**
 * @enum CellOwner
 * Options for cell ownership.
 */
enum CellOwner {
    NONE,
    X,
    O,
};

using LLCell = CellOwner;

const unsigned int CELL_COUNT = 9;
const unsigned int SYMBOL_COUNT = 3;

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER);

#endif // !SHARED
