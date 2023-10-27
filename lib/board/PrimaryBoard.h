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
    static std::array<const char *, 3> _symbols;
    std::array<LeafBoard *, 9> _cells;

public:
    PrimaryBoard(std::shared_ptr<NcHandler> ncHandler);
    ~PrimaryBoard();
    CellOwner get_cell_owner(const int INDEX) const override final;
    std::optional<LeafBoard *> select_board(const int INDEX) const;

    void draw_x(const unsigned int INDEX) override final;
    void draw_o(const unsigned int INDEX) override final;
};

// Helper functions
ncplane_options def_primary_nopts(std::shared_ptr<NcHandler> ncHandler);

#endif // !PRIMARYBOARD
