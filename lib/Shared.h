#ifndef SHARED
#define SHARED

#include <ostream>

enum CellOwner {
    None,
    Player1,
    Player2,
};

typedef char LLCell;

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER);

#endif // !SHARED
