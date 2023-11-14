#include "lib/board/PrimaryBoard.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/ABoard.h"
#include "lib/board/LeafBoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/IGraphicalBoard.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>
#include <optional>

const std::array<const char *, SYMBOL_COUNT> PrimaryBoard::_symbols =
    std::array<const char *, SYMBOL_COUNT>({"\u2501", "\u2503", "\u254B"});

PrimaryBoard::PrimaryBoard(INcHandler *const P_ncHandler,
                           std::unique_ptr<IGraphicalBoard> gBoard)
    : ABoard::ABoard{P_ncHandler}, _gBoard{std::move(gBoard)}, _cells{} {
    init_cells();
}

PrimaryBoard::PrimaryBoard(INcHandler *const P_ncHandler)
    : ABoard::ABoard{P_ncHandler},
      _gBoard{std::unique_ptr<IGraphicalBoard>{new PrimaryGraphicalBoard{
          P_ncHandler, PrimaryBoard::defPrimaryNopts(P_ncHandler)}}},
      _cells{} {
    init_cells();
}

LeafBoard *PrimaryBoard::getLeafBoard(const int INDEX) const {
    return _cells.at(gsl::narrow<unsigned int>(INDEX)).get();
}

IGraphicalBoard *PrimaryBoard::getGraphicalBoard() const {
    return _gBoard.get();
}

void PrimaryBoard::init_cells() {
    std::array<IGraphicalArea *, CELL_COUNT> gBoards =
        getGraphicalBoard()->get_children();

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        _cells.at(i) = std::make_unique<LeafBoard>(
            getNcHandler(), dynamic_cast<IGraphicalBoard *>(gBoards.at(i)));
    }
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX))->get_winner();
}

void PrimaryBoard::draw() {
    getGraphicalBoard()->draw_board(_symbols,
                                    getNcHandler()->get_default_channels());

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        LeafBoard *const P_cell = _cells.at(i).get();
        P_cell->draw();
    }
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    LeafBoard *const P_cell = _cells.at(gsl::narrow<unsigned int>(INDEX)).get();
    const std::optional<LeafBoard *> OPT = std::optional(P_cell);

    return P_cell->get_winner() == NONE ? OPT : std::nullopt;
}

ncplane_options PrimaryBoard::defPrimaryNopts(INcHandler *const P_ncHandler) {
    auto stdPlane =
        std::unique_ptr<INcPlaneWrapper>{P_ncHandler->get_stdplane_wrapper()};

    const int ROWS = (3 * 11) + 2;
    const int COLS = (3 * 20) + 2;

    int stdRows{0}, stdCols{0};
    stdPlane->dim_yx(stdRows, stdCols);

    int stdCenterY{0}, stdCenterX{0};
    stdCenterY = stdRows / 2;
    stdCenterX = stdCols / 2;

    int boardOriginY{0}, boardOriginX{0};
    boardOriginY = stdCenterY - (ROWS / 2);
    boardOriginX = stdCenterX - (COLS / 2);

    ncplane_options nopts = {
        boardOriginY, boardOriginX, ROWS, COLS, nullptr,
        nullptr,      nullptr,      0,    0,    0,
    };

    return nopts;
}
