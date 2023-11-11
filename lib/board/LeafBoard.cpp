#include "lib/board/LeafBoard.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

std::array<const char *, 3> LeafBoard::_symbols =
    std::array<const char *, 3>({"\u2500", "\u2502", "\u253C"});

LeafBoard::LeafBoard(std::shared_ptr<NcHandler> ncHandler,
                     std::unique_ptr<GraphicalBoard> gBoard)
    : Board::Board(ncHandler, std::move(gBoard)) {}

LeafBoard::LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE)
    : Board::Board(ncHandler, PLANE) {
    _cells = std::array<LLCell, 9>();
    _winner = None;
}

CellOwner LeafBoard::get_cell_owner(const unsigned int INDEX) const {
    return _cells.at(INDEX);
}

bool LeafBoard::set_cell_owner(const unsigned int INDEX,
                               const CellOwner OWNER) {
    if (_cells.at(INDEX) == None) {
        _cells.at(INDEX) = OWNER;

        if (check_win(INDEX, OWNER)) {
            _winner = OWNER;
        }
        return true;
    }
    return false;
}

CellOwner LeafBoard::get_winner() const {
    return _winner;
}

void LeafBoard::fill_x() {
    getGraphicalBoard()->fill_x();
}

void LeafBoard::fill_o() {
    getGraphicalBoard()->fill_o();
}

void LeafBoard::draw() {
    getGraphicalBoard()->draw_board(
        _symbols,
        NcHandler::combine_channels(getNcHandler()->get_default_bg_channel(),
                                    NcHandler::GREY_CHANNEL));
}
