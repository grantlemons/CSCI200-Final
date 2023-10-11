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
    bool check_win(const int INDEX, const CellOwner OWNER) const;
    void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

#endif // !LEAFBOARD
