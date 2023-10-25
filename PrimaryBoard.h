#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "Shared.h"
#include "LeafBoard.h"
#include "Board.h"

#include <optional>
#include <array>

class PrimaryBoard : virtual public Board {
private:
    std::array<LeafBoard *, 9> _cells;

public:
    PrimaryBoard(std::shared_ptr<NcHandler> ncHandler);
    ~PrimaryBoard() = default;
    CellOwner get_cell_owner(const int INDEX) const;
    std::optional<LeafBoard *> select_board(const int INDEX) const;
};

#endif // !PRIMARYBOARD
