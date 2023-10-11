#ifndef LEAFBOARD
#define LEAFBOARD

#include "Board.h"
#include "Shared.cpp"

class LeafBoard : virtual public Board {
private:
    LLCell cells[9];

public:
    LeafBoard();
    bool check_win(const int INDEX, const CellOwner OWNER) const;
    void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

#endif // !LEAFBOARD
