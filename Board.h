#ifndef BOARD
#define BOARD

#include "Shared.h"
#include <optional>
#include <ostream>

class Board {
public:
    Board() = default;
    virtual ~Board() = default;
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const;
    virtual CellOwner get_cell_owner(const int INDEX) const = 0;

    friend std::ostream &operator<<(std::ostream &out, const Board &BRD);
};

#endif // !BOARD
