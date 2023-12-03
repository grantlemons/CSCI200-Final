#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/BoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>
#include <optional>

void gameloop(const CELL_OWNER PLAYER, PrimaryBoard *const pBoard,
              LeafBoard *pSelected);

int main() {
    std::unique_ptr<AbstractBoardFactory> factory{new BoardFactory()};
    PrimaryBoard *pBoard = factory->getPrimaryBoard();

    pBoard->draw();

    CELL_OWNER victor = NONE;
    LeafBoard *pSelected = nullptr;
    std::optional<LeafBoard *> opt = nullptr;

    CELL_OWNER player = X;
    while (victor == NONE) {
        gameloop(player, pBoard, pSelected);
        factory->getNcHandler()->render();

        player = get_other_player(player);
    }

    return EXIT_SUCCESS;
}

void gameloop(const CELL_OWNER PLAYER, PrimaryBoard *const pBoard,
              LeafBoard *pSelected) {
    // select leaf board if needed
    while (pSelected == nullptr) {
        const int SELECTION = 0; // TODO take input for selection instead
        // see notcurses_get_nblock(struct notcurses* n, ncinput* ni)

        std::optional<LeafBoard *> opt = pBoard->select_board(SELECTION);

        if (opt != std::nullopt) {
            pSelected = opt.value();
        }
    }

    // select cell of leafboard
    int selection = 0;
    bool selected = false;
    while (!selected) {
        // TODO take input for selection here
        // see notcurses_get_nblock(struct notcurses* n, ncinput* ni)

        selected = pSelected->get_cell_owner(selection) == NONE;
    }
    pSelected->set_cell_owner(selection, PLAYER);

    // exit leaf board if won
    if (pSelected->get_winner() != NONE) {
        pSelected = nullptr;
    }
}
