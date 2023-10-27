#ifndef LEAFBOARD
#define LEAFBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"

#include <array>
#include <memory>
#include <notcurses/notcurses.h>

class LeafBoard : virtual public Board {
private:
    static std::array<const char *, 3> _symbols;
    std::array<LLCell, 9> _cells;

public:
    CellOwner winner;

public:
    LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE);
    ~LeafBoard() = default;
    CellOwner get_cell_owner(const int INDEX) const;
    bool set_cell_owner(const int INDEX, const CellOwner OWNER);

    void fill_x();
    void fill_o();
};

#endif // !LEAFBOARD
