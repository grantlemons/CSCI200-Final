#ifndef LEAFBOARD
#define LEAFBOARD

#include "Board.h"
#include "Shared.h"
#include <notcurses/notcurses.h>

class LeafBoard : virtual public Board {
private:
    LLCell *_cells;

public:
    CellOwner winner;

public:
    LeafBoard();
    ~LeafBoard() = default;
    CellOwner get_cell_owner(const int INDEX) const;
    bool set_cell_owner(const int INDEX, const CellOwner OWNER);
};

#endif // !LEAFBOARD
