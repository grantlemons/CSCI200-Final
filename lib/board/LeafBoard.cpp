#include "lib/board/LeafBoard.h"

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/GraphicalBoard.h"

#include <array>
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

const char *THIN_SYMBOLS[3] = {"\u2500", "\u2502", "\u253C"};

uint64_t def_thin_channels(std::shared_ptr<NcHandler> ncHandler) {
    const uint32_t THIN_FG_CHANNEL = NCCHANNEL_INITIALIZER(0x00, 0xff, 0xff);
    const uint32_t THIN_BG_CHANNEL =
        ncplane_bchannel(ncHandler->get_stdplane());
    const uint64_t THIN_CHANNELS =
        ((uint64_t)THIN_FG_CHANNEL << 32ull) + THIN_BG_CHANNEL;

    return THIN_CHANNELS;
}

LeafBoard::LeafBoard(std::shared_ptr<NcHandler> ncHandler, ncplane *const PLANE)
    : Board::Board(ncHandler, PLANE, def_thin_channels(ncHandler),
                   THIN_SYMBOLS) {
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
