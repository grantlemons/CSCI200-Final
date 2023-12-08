/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/board/LeafBoard.h"

#include "gsl/assert"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/ABoard.h"
#include "lib/interfaces/IGraphicalBoard.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>

const std::array<const char *, SYMBOL_COUNT> LeafBoard::_SYMBOLS =
    std::array<const char *, SYMBOL_COUNT>{"\u2500", "\u2502", "\u253C"};

LeafBoard::LeafBoard(INcHandler *const P_ncHandler,
                     IGraphicalBoard *const P_gBoard)
    : ABoard::ABoard{P_ncHandler}, _pGBoard{P_gBoard}, _cells{}, _winner{NONE} {
}

IGraphicalBoard *LeafBoard::getGraphicalBoard() const {
    return _pGBoard;
}

CELL_OWNER LeafBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX));
}

bool LeafBoard::isTie() const {
    return _winner == NONE &&
           std::find(_cells.begin(), _cells.end(), NONE) == _cells.end();
}

void LeafBoard::set_cell_owner(const int INDEX, const CELL_OWNER OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);
    Expects(_cells.at(gsl::narrow<unsigned int>(INDEX)) == NONE);

    _cells.at(gsl::narrow<unsigned int>(INDEX)) = OWNER;
    mark_cell(INDEX, OWNER);

    if (check_win(INDEX, OWNER)) {
        _winner = OWNER;
    } else if (isTie()) {
        _winner = TIE;
    }

    Ensures(_cells.at(gsl::narrow<unsigned int>(INDEX)) == OWNER);
}

CELL_OWNER LeafBoard::get_winner() const {
    return _winner;
}

void LeafBoard::draw() {
    getGraphicalBoard()->draw_board(
        _SYMBOLS,
        NcHandler::combineChannels(getNcHandler()->get_default_bg_channel(),
                                   NcHandler::GREY_CHANNEL));
}
