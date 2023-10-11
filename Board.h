#ifndef BOARD
#define BOARD

#include "Shared.cpp"
#include <optional>

class Board {
public:
    CellOwner winner;

    Board();
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const;
};

#endif // !BOARD
