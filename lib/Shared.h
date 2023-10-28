#ifndef SHARED
#define SHARED

#include <ostream>

enum CellOwner {
    None,
    X,
    O,
};

typedef CellOwner LLCell;

std::ostream &operator<<(std::ostream &out, const CellOwner OWNER);

#endif // !SHARED
