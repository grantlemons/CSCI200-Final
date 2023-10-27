#ifndef BOARD
#define BOARD

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/GraphicalBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>

class Board {
protected:
    GraphicalBoard mGBoard;

    Board(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE,
          const uint64_t CELL_CHANNELS, std::array<const char *, 3> SYMBOLS);
    Board(std::shared_ptr<NcHandler> ncHandler, const ncplane_options NOPTS,
          const uint64_t CELL_CHANNELS, std::array<const char *, 3> SYMBOLS);
    virtual ~Board() = default;

public:
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const;
    virtual CellOwner get_cell_owner(const int INDEX) const = 0;

    virtual void draw();
    virtual void draw_x(const unsigned int INDEX);
    virtual void draw_o(const unsigned int INDEX);

    friend std::ostream &operator<<(std::ostream &out, const Board &BRD);
};

// Helper functions
unsigned int negative_mod(int a, int b);
void horizontal_others(const int INDEX, int &other1, int &other2);
void vertical_others(const int INDEX, int &other1, int &other2);
void diagonal_fours_others(const int INDEX, int &other1, int &other2);
void diagonal_twos_others(const int INDEX, int &other1, int &other2);

#endif // !BOARD
