#include "Shared.h"
#include "Board.h"
#include "PrimaryBoard.h"
#include "LeafBoard.h"

#include <cstdint>
#include <notcurses/notcurses.h>
#include <optional>
#include <vector>

const char *THICK_SYMBOLS[3] = {"\u2501", "\u2503", "\u254B"};

uint64_t def_thick_channels(std::shared_ptr<NcHandler> ncHandler) {
    const uint64_t THICK_CHANNELS = ncplane_channels(ncHandler->get_stdplane());

    return THICK_CHANNELS;
}

PrimaryBoard::PrimaryBoard(std::shared_ptr<NcHandler> ncHandler)
    : Board::Board(ncHandler, def_thick_channels(ncHandler), THICK_SYMBOLS) {
    std::vector<LeafBoard> tmp;

    for (int i = 0; i < 9; i++) {
        tmp.push_back(
            LeafBoard(ncHandler, this->get_gboard()->get_child_planes()[i]));
    }

    this->_cells = tmp.data();
}

CellOwner PrimaryBoard::get_cell_owner(const int INDEX) const {
    return this->_cells[INDEX].winner;
}

std::optional<LeafBoard *> PrimaryBoard::select_board(const int INDEX) const {
    LeafBoard *cell = &this->_cells[INDEX];
    std::optional<LeafBoard *> opt = std::optional(cell);

    return cell->winner == None ? opt : std::nullopt;
}
