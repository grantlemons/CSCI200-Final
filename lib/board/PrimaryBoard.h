#ifndef PRIMARYBOARD
#define PRIMARYBOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"

#include <array>
#include <memory>
#include <optional>

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
