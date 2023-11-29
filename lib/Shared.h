#ifndef SHARED
#define SHARED

#include <ostream>

/**
 * @enum CELL_OWNER
 * Options for cell ownership.
 */
enum CELL_OWNER {
    NONE,
    X,
    O,
};

using LLCell = CELL_OWNER;

const unsigned int CELL_COUNT = 9;
const unsigned int SYMBOL_COUNT = 3;

std::ostream &operator<<(std::ostream &out, const CELL_OWNER OWNER);

#endif // !SHARED
