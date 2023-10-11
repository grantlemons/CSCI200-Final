#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "Shared.cpp"
#include "LeafBoard.h"
#include "Board.h"
#include <optional>

class PrimaryBoard : virtual public Board {
private:
    LeafBoard cells[9];

public:
    PrimaryBoard();
    bool check_win(const int INDEX, const CellOwner OWNER) const;
    std::optional<LeafBoard *> select_board(const int INDEX) const;
};

#endif // !PRIMARYBOARD
