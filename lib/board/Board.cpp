#include "lib/board/Board.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/GraphicalBoard.h"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <cmath>
#include <iostream>
#include <memory>
#include <notcurses/notcurses.h>
#include <ostream>

Board::Board(std::shared_ptr<NcHandlerI> ncHandler,
             std::unique_ptr<GraphicalBoardI> gBoard)
    : _ncHandler{ncHandler}, _gBoard{std::move(gBoard)} {}

Board::Board(std::shared_ptr<NcHandlerI> ncHandler,
             std::unique_ptr<NcPlaneWrapperI> plane)
    : _ncHandler{ncHandler},
      _gBoard{new GraphicalBoard{ncHandler.get(), std::move(plane)}} {}

Board::Board(std::shared_ptr<NcHandlerI> ncHandler, const ncplane_options NOPTS)
    : _ncHandler{ncHandler},
      _gBoard{new GraphicalBoard{ncHandler.get(), NOPTS}} {}

GraphicalBoardI *Board::getGraphicalBoard() const {
    return _gBoard.get();
}

std::shared_ptr<NcHandlerI> Board::getNcHandler() const {
    return _ncHandler;
}

bool Board::check_win(const int INDEX, const CellOwner OWNER) const {
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

void Board::mark_cell(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);

    switch (OWNER) {
    case X:
        _gBoard->draw_x(INDEX);
        break;
    case O:
        _gBoard->draw_o(INDEX);
        break;
    default:
        break;
    }
}

std::ostream &operator<<(std::ostream &out, const Board &BRD) {
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
