#include "lib/board/PrimaryBoard.h"

#include "gsl/assert"
#include "gsl/narrow"
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

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    Expects(INDEX >= 0 && INDEX <= 9);

    return _cells.at(gsl::narrow<unsigned int>(INDEX))->get_winner();
}

void PrimaryBoard::draw() {
    getGraphicalBoard()->draw_board(_symbols,
                                    getNcHandler()->get_default_channels());

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        LeafBoard *cell = _cells.at(i).get();
        cell->draw();
    }
}

void PrimaryBoard::mark_cell(const int INDEX, const CellOwner OWNER) {
    Expects(INDEX >= 0 && INDEX <= 9);

    switch (OWNER) {
    case X:
        getGraphicalBoard()->draw_x(INDEX);
        _cells.at(gsl::narrow<unsigned int>(INDEX))->mark_fill(OWNER);
        break;
    case O:
        getGraphicalBoard()->draw_o(INDEX);
        _cells.at(gsl::narrow<unsigned int>(INDEX))->mark_fill(OWNER);
        break;
    default:
        break;
    }
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) {
    Expects(INDEX >= 0 && INDEX <= 9);

    LeafBoard *cell = _cells.at(gsl::narrow<unsigned int>(INDEX)).get();
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->get_winner() == None ? opt : std::nullopt;
}

ncplane_options def_primary_nopts(std::shared_ptr<NcHandlerI> ncHandler) {
    NcPlaneWrapperI *stdPlane = ncHandler->get_stdplane_wrapper();

    const int ROWS = (3 * 11) + 2;
    const int COLS = (3 * 20) + 2;

    int std_rows{0}, std_cols{0};
    stdPlane->dim_yx(std_rows, std_cols);

    delete stdPlane;

    int std_center_y, std_center_x;
    std_center_y = std_rows / 2;
    std_center_x = std_cols / 2;

    int board_origin_y, board_origin_x;
    board_origin_y = std_center_y - (ROWS / 2);
    board_origin_x = std_center_x - (COLS / 2);

    ncplane_options nopts = {
        board_origin_y, board_origin_x, ROWS, COLS, nullptr,
        nullptr,        nullptr,        0,    0,    0,
    };

    return nopts;
}
