#ifndef LEAFBOARD
#define LEAFBOARD

#include "Board.h"
#include "Shared.h"

class LeafBoard : virtual public Board {
private:
    LLCell *cells;

public:
    LeafBoard();
    ~LeafBoard();
    CellOwner get_cell_owner(const int INDEX) const;
    void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

#endif // !LEAFBOARD
