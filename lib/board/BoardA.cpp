#include "lib/board/BoardA.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/GraphicalBoardI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <cmath>
#include <memory>
#include <notcurses/notcurses.h>
#include <ostream>

BoardA::BoardA(std::shared_ptr<NcHandlerI> ncHandler) : _ncHandler{ncHandler} {}

std::shared_ptr<NcHandlerI> BoardA::getNcHandler() const {
    return _ncHandler;
}

bool BoardA::check_win(const int INDEX, const CellOwner OWNER) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    int horizontal_other1, horizontal_other2, vertical_other1, vertical_other2;

    horizontal_others(INDEX, horizontal_other1, horizontal_other2);
    vertical_others(INDEX, vertical_other1, vertical_other2);

    // set diagonal_other indexes
    // diagonals are only sometimes valid:
    // |0| |2|
    // | |4| |
    // |6| |8|
    bool include_diagonals2{false};
    bool include_diagonals4{false};

    int diagonal_other1{0}, diagonal_other2{0};
    int diagonal_other3{0}, diagonal_other4{0};
    if (INDEX == 4) {
        include_diagonals2 = true;
        include_diagonals4 = true;
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 4 == 0) {
        include_diagonals4 = true;
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 2 == 0) {
        include_diagonals2 = true;
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
    }
    const bool WON_HORI = get_cell_owner(horizontal_other1) == OWNER &&
                          get_cell_owner(horizontal_other2) == OWNER;
    const bool WON_VERT = get_cell_owner(vertical_other1) == OWNER &&
                          get_cell_owner(vertical_other2) == OWNER;
    const bool WON_DIAGONAL_TWOS = include_diagonals2 &&
                                   get_cell_owner(diagonal_other1) == OWNER &&
                                   get_cell_owner(diagonal_other2) == OWNER;
    const bool WON_DIAGONALS_FOURS = include_diagonals4 &&
                                     get_cell_owner(diagonal_other3) == OWNER &&
                                     get_cell_owner(diagonal_other4) == OWNER;

    bool res =
        get_cell_owner(INDEX) == OWNER &&
        (WON_HORI || WON_VERT || WON_DIAGONAL_TWOS || WON_DIAGONALS_FOURS);

    return res;
}

void BoardA::mark_cell(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);

    switch (OWNER) {
    case X:
        getGraphicalBoard()->draw_x(INDEX);
        break;
    case O:
        getGraphicalBoard()->draw_o(INDEX);
        break;
    default:
        break;
    }
}

std::ostream &operator<<(std::ostream &out, const BoardA &BRD) {
    out << "[";
    for (int i = 0; i < gsl::narrow<int>(CELL_COUNT - 1); i++) {
        out << BRD.get_cell_owner(i) << ", ";

        if ((i + 1) % 3 == 0) {
            out << std::endl << " ";
        }
    }
    out << BRD.get_cell_owner(8) << "]";

    return out;
}
