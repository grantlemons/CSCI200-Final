#include "lib/board/Board.h"

#include "lib/GraphicalBoard.h"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <array>
#include <cmath>
#include <memory>
#include <notcurses/notcurses.h>
#include <ostream>

Board::Board(std::shared_ptr<NcHandlerI> ncHandler,
             std::unique_ptr<GraphicalBoardI> gBoard)
    : _ncHandler(ncHandler), _gBoard(std::move(gBoard)) {}

Board::Board(std::shared_ptr<NcHandlerI> ncHandler,
             std::unique_ptr<NcPlaneWrapperI> plane)
    : _ncHandler(ncHandler),
      _gBoard(new GraphicalBoard(ncHandler.get(), std::move(plane))) {}

Board::Board(std::shared_ptr<NcHandlerI> ncHandler, const ncplane_options NOPTS)
    : _ncHandler(ncHandler),
      _gBoard(new GraphicalBoard(ncHandler.get(), NOPTS)) {}

GraphicalBoardI *Board::getGraphicalBoard() const {
    return _gBoard.get();
}

std::shared_ptr<NcHandlerI> Board::getNcHandler() const {
    return _ncHandler;
}

bool Board::check_win(const unsigned int INDEX, const CellOwner OWNER) const {
    unsigned int horizontal_other1, horizontal_other2, vertical_other1,
        vertical_other2;

    horizontal_others(INDEX, horizontal_other1, horizontal_other2);
    vertical_others(INDEX, vertical_other1, vertical_other2);

    // set diagonal_other indexes
    // diagonals are only sometimes valid:
    // |0| |2|
    // | |4| |
    // |6| |8|
    bool include_diagonals2 = true;
    bool include_diagonals4 = true;
    unsigned int diagonal_other1 = 0, diagonal_other2 = 0;
    unsigned int diagonal_other3 = 0, diagonal_other4 = 0;
    if (INDEX == 4) {
        diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 4 == 0) {
        include_diagonals2 = false;
        diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
    } else if (INDEX % 2 == 0) {
        include_diagonals4 = false;
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

    return WON_HORI || WON_VERT || WON_DIAGONAL_TWOS || WON_DIAGONALS_FOURS;
}

void Board::mark_cell(const unsigned int INDEX, const CellOwner OWNER) {
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

constexpr unsigned int negative_mod(const int A, const int B) {
    return static_cast<unsigned int>(
        A - (B * static_cast<int>(floor(static_cast<double>(A) / B))));
}

constexpr void horizontal_others(const unsigned int INDEX, unsigned int &other1,
                                 unsigned int &other2) {
    const unsigned int ROW_LEN = 3;

    other1 = negative_mod(static_cast<int>(INDEX - 1u), ROW_LEN);
    other2 = (INDEX + 1u) % ROW_LEN;
}
constexpr void vertical_others(const unsigned int INDEX, unsigned int &other1,
                               unsigned int &other2) {
    const unsigned int ROW_LEN = 3;

    other1 = negative_mod(static_cast<int>(INDEX - ROW_LEN), CELL_COUNT);
    other2 = (INDEX + ROW_LEN) % CELL_COUNT;
}
constexpr void diagonal_fours_others(const unsigned int INDEX,
                                     unsigned int &other1,
                                     unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 4u), CELL_COUNT + 3u);
    other2 = (INDEX + 4u) % CELL_COUNT + 3u;
}
constexpr void diagonal_twos_others(const unsigned int INDEX,
                                    unsigned int &other1,
                                    unsigned int &other2) {
    other1 = negative_mod(static_cast<int>(INDEX - 2u), CELL_COUNT + 1u);
    other2 = (INDEX + 2u) % CELL_COUNT + 1u;
}

std::ostream &operator<<(std::ostream &out, const Board &BRD) {
    out << "[";
    for (unsigned int i = 0; i < CELL_COUNT - 1; i++) {
        out << BRD.get_cell_owner(i) << ", ";

        if ((i + 1) % 3 == 0) {
            out << std::endl << " ";
        }
    }
    out << BRD.get_cell_owner(8) << "]";

    return out;
}
