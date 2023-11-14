#include "lib/board/LeafBoard.h"

#include "gsl/assert"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/ABoard.h"
#include "lib/interfaces/IGraphicalBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

const std::array<const char *, SYMBOL_COUNT> LeafBoard::_symbols =
    std::array<const char *, SYMBOL_COUNT>{"\u2500", "\u2502", "\u253C"};

LeafBoard::LeafBoard(INcHandler *const P_ncHandler,
                     IGraphicalBoard *const P_gBoard)
    : ABoard::ABoard{P_ncHandler}, _pGBoard{P_gBoard}, _cells{}, _winner{NONE} {
}

IGraphicalBoard *LeafBoard::getGraphicalBoard() const {
    return _pGBoard;
}

CellOwner LeafBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX));
}

void LeafBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);
    Expects(_cells.at(gsl::narrow<unsigned int>(INDEX)) == NONE);

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
        NcHandler::combineChannels(getNcHandler()->get_default_bg_channel(),
                                   NcHandler::GREY_CHANNEL));
}
