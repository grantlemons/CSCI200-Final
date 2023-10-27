#include "lib/board/LeafBoard.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/GraphicalBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

std::array<const char *, 3> LeafBoard::_symbols =
    std::array<const char *, 3>({"\u2500", "\u2502", "\u253C"});

LeafBoard::LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE)
    : Board::Board(
          ncHandler, PLANE,
          NcHandler::combine_channels(ncHandler->get_default_bg_channel(),
                                      NcHandler::GREY_CHANNEL),
          LeafBoard::_symbols) {
    this->_cells = std::array<LLCell, 9>();
    this->winner = None;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    return (CellOwner)this->_cells.at(INDEX);
}

// navigation
bool LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    if (this->_cells.at(INDEX) == None) {
        this->_cells.at(INDEX) = OWNER;

        if (this->check_win(INDEX, OWNER)) {
            this->winner = OWNER;
        }
        return true;
    }
    return false;
}

void LeafBoard::fill_x() {
    this->_gboard.fill_x();
}

void LeafBoard::fill_o() {
    this->_gboard.fill_o();
}
