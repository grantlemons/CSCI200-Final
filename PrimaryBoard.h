#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "Shared.h"
#include "LeafBoard.h"
#include "Board.h"

#include <optional>

class PrimaryBoard : virtual public Board {
private:
    LeafBoard *_cells;

public:
    PrimaryBoard();
    ~PrimaryBoard() = default;
    CellOwner get_cell_owner(const int INDEX) const;
    std::optional<LeafBoard *> select_board(const int INDEX) const;
};

#endif // !PRIMARYBOARD
