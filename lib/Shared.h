#ifndef SHARED
#define SHARED

#include <iostream>
#include <ostream>

/**
 * @enum CELL_OWNER
 * Options for cell ownership.
 */
enum CELL_OWNER {
    NONE,
    TIE,
    X,
    O,
};

using LLCell = CELL_OWNER;

const unsigned int CELL_COUNT = 9;
const unsigned int SYMBOL_COUNT = 3;

std::ostream &operator<<(std::ostream &out, const CELL_OWNER OWNER);
CELL_OWNER get_other_player(const CELL_OWNER PLAYER);

#endif // !SHARED
