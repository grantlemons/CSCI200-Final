#ifndef BOARD
#define BOARD

#include "GraphicalBoard.h"
#include "NcHandler.h"
#include "Shared.h"
#include <memory>
#include <optional>
#include <ostream>

class Board {
private:
    GraphicalBoard _gboard;

public:
    Board(std::shared_ptr<NcHandler> ncHandler, const char **const SYMBOLS);
    Board(std::shared_ptr<NcHandler> ncHandler, ncplane_options nopts,
          const char **const SYMBOLS);
    virtual ~Board() = default;
    virtual bool check_win(const int INDEX, const CellOwner OWNER) const;
    virtual CellOwner get_cell_owner(const int INDEX) const = 0;

    friend std::ostream &operator<<(std::ostream &out, const Board &BRD);
};

// Helper functions
unsigned int negative_mod(int a, int b);
void horizontal_others(const int INDEX, int &other1, int &other2);
void vertical_others(const int INDEX, int &other1, int &other2);
void diagonal_fours_others(const int INDEX, int &other1, int &other2);
void diagonal_twos_others(const int INDEX, int &other1, int &other2);

#endif // !BOARD
