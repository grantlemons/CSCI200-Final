#ifndef LEAFBOARD
#define LEAFBOARD

#include "Board.h"
#include "Shared.h"

#include <array>
#include <notcurses/notcurses.h>

class LeafBoard : virtual public Board {
private:
    std::array<LLCell, 9> _cells;

public:
    CellOwner winner;

public:
    LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE);
    ~LeafBoard() = default;
    CellOwner get_cell_owner(const int INDEX) const;
    bool set_cell_owner(const int INDEX, const CellOwner OWNER);
};

#endif // !LEAFBOARD
