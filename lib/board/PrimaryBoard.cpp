#include "lib/board/PrimaryBoard.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>
#include <optional>

std::array<const char *, SYMBOL_COUNT> PrimaryBoard::_symbols =
    std::array<const char *, SYMBOL_COUNT>({"\u2501", "\u2503", "\u254B"});

PrimaryBoard::PrimaryBoard(std::shared_ptr<NcHandlerI> ncHandler,
                           std::unique_ptr<GraphicalBoardI> gBoard)
    : Board::Board(ncHandler, std::move(gBoard)), _cells() {
    init_cells();
}

PrimaryBoard::PrimaryBoard(std::shared_ptr<NcHandlerI> ncHandler)
    : Board::Board(ncHandler, def_primary_nopts(ncHandler)), _cells() {
    init_cells();
}

void PrimaryBoard::init_cells() {
    std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT> gBoards =
        getGraphicalBoard()->create_child_boards();

    for (unsigned int i = 0; i < 9; i++) {
        _cells.at(i) = std::unique_ptr<LeafBoard>(
            new LeafBoard(getNcHandler(), std::move(gBoards.at(i))));
    }
}

CellOwner PrimaryBoard::get_cell_owner(const unsigned int INDEX) const {
    return _cells.at(INDEX)->get_winner();
}

void PrimaryBoard::draw() {
    getGraphicalBoard()->draw_board(_symbols,
                                    getNcHandler()->get_default_channels());

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        LeafBoard *cell = _cells.at(i).get();
        cell->draw();
    }
}

void PrimaryBoard::mark_cell(const unsigned int INDEX, const CellOwner OWNER) {
    switch (OWNER) {
    case X:
        getGraphicalBoard()->draw_x(INDEX);
        _cells.at(INDEX)->mark_fill(OWNER);
        break;
    case O:
        getGraphicalBoard()->draw_o(INDEX);
        _cells.at(INDEX)->mark_fill(OWNER);
        break;
    default:
        break;
    }
}

std::optional<LeafBoard *>
PrimaryBoard::select_board(const unsigned int INDEX) {
    LeafBoard *cell = _cells.at(INDEX).get();
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->get_winner() == None ? opt : std::nullopt;
}

ncplane_options def_primary_nopts(std::shared_ptr<NcHandlerI> ncHandler) {
    NcPlaneWrapperI *stdPlane = ncHandler->get_stdplane_wrapper();

    const unsigned int ROWS = (3u * 11u) + 2u;
    const unsigned int COLS = (3u * 20u) + 2u;

    unsigned int std_rows{0}, std_cols{0};
    stdPlane->dim_yx(&std_rows, &std_cols);

    delete stdPlane;

    unsigned int std_center_y, std_center_x;
    std_center_y = std_rows / 2u;
    std_center_x = std_cols / 2u;

    int board_origin_y, board_origin_x;
    board_origin_y = static_cast<int>(std_center_y - (ROWS / 2u));
    board_origin_x = static_cast<int>(std_center_x - (COLS / 2u));

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, nullptr,
        nullptr,        nullptr,        0,    0,    0,
    };

    return nopts;
}
