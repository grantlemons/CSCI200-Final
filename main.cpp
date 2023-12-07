#include "gsl/narrow"
#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/BoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>
#include <optional>

int get_selection_blocking(INcHandler *const P_nchandler);
void gameloop(INcHandler *const P_nchandler, const CELL_OWNER PLAYER,
              PrimaryBoard *const P_board, LeafBoard *&pSelected);

int main() {
    std::unique_ptr<AbstractBoardFactory> factory{new BoardFactory()};
    PrimaryBoard *pBoard = factory->getPrimaryBoard();

    pBoard->draw();

    CELL_OWNER victor = NONE;
    LeafBoard *pSelected = nullptr;
    std::optional<LeafBoard *> opt = nullptr;

    CELL_OWNER player = X;
    while (victor == NONE) {
        gameloop(factory->getNcHandler(), player, pBoard, pSelected);
        factory->getNcHandler()->render();

        player = get_other_player(player);
    }

    return EXIT_SUCCESS;
}

int get_selection_blocking(INcHandler *const P_nchandler) {
    const int MAX_IN = '8';
    const int MIN_IN = '0';

    uint32_t res{0};
    ncinput in;
    while (in.evtype != NCTYPE_PRESS || !(res <= MAX_IN && res >= MIN_IN)) {
        res = P_nchandler->get_blocking(&in);
    }

    int number = gsl::narrow<int>(res - MIN_IN);
    return number;
}

void gameloop(INcHandler *const P_nchandler, const CELL_OWNER PLAYER,
              PrimaryBoard *const P_board, LeafBoard *&pSelected) {
    // select leaf board if needed
    while (pSelected == nullptr) {
        const int SELECTION{get_selection_blocking(P_nchandler)};
        std::optional<LeafBoard *> opt{P_board->select_board(SELECTION)};

        if (opt != std::nullopt) {
            pSelected = opt.value();
        }
    }

    // select cell of leafboard
    int selection{0};
    bool selected{false};
    while (!selected) {
        selection = get_selection_blocking(P_nchandler);
        selected = pSelected->get_cell_owner(selection) == NONE;
    }
    pSelected->set_cell_owner(selection, PLAYER);

    // select next board if valid
    const CELL_OWNER WINNER = pSelected->get_winner();
    if (WINNER != NONE) {
        P_board->mark_cell(P_board->selected, WINNER);
        pSelected = P_board->select_board(selection).value_or(nullptr);
    }
}
