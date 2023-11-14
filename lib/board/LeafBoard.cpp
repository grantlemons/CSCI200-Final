#include "lib/board/LeafBoard.h"

#include "gsl/assert"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/BoardA.h"
#include "lib/interfaces/GraphicalBoardI.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

std::array<const char *, SYMBOL_COUNT> LeafBoard::_symbols =
    std::array<const char *, SYMBOL_COUNT>{"\u2500", "\u2502", "\u253C"};

LeafBoard::LeafBoard(NcHandlerI *ncHandler, GraphicalBoardI *gBoard)
    : BoardA::BoardA{ncHandler}, _gBoard{gBoard}, _cells{}, _winner{None} {}

GraphicalBoardI *LeafBoard::getGraphicalBoard() const {
    return _gBoard;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX));
}

void LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);
    Expects(_cells.at(gsl::narrow<unsigned int>(INDEX)) == None);

    _cells.at(gsl::narrow<unsigned int>(INDEX)) = OWNER;
    mark_cell(INDEX, OWNER);

    if (check_win(INDEX, OWNER)) {
        _winner = OWNER;
    }

    Ensures(_cells.at(gsl::narrow<unsigned int>(INDEX)) == OWNER);
}

CellOwner LeafBoard::get_winner() const {
    return _winner;
}

void LeafBoard::draw() {
    getGraphicalBoard()->draw_board(
        _symbols,
        NcHandler::combine_channels(getNcHandler()->get_default_bg_channel(),
                                    NcHandler::GREY_CHANNEL));
}
