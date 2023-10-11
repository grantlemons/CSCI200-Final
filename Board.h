#ifndef BOARD
#define BOARD

#include "Shared.h"
#include <optional>

class Board {
public:
    CellOwner winner;

    Board();
    virtual ~Board() = default;
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const = 0;
};

#endif // !BOARD
