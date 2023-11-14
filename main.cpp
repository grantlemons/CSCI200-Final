#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/BoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>
#include <optional>

int main() {
    std::unique_ptr<AbstractBoardFactory> factory{new BoardFactory()};
    PrimaryBoard *pBoard = factory->getPrimaryBoard();

    pBoard->draw();

    CellOwner victor = NONE;
    LeafBoard *pSelected = nullptr;
    std::optional<LeafBoard *> opt = nullptr;

    opt = pBoard->select_board(2);
    if (opt != std::nullopt) {
        pSelected = opt.value();
        pSelected->set_cell_owner(0, X);
    }
    opt = pBoard->select_board(0);
    if (opt != std::nullopt) {
        pSelected = opt.value();
        pSelected->set_cell_owner(2, O);
    }
    opt = pBoard->select_board(2);
    if (opt != std::nullopt) {
        pSelected = opt.value();
        pSelected->set_cell_owner(1, X);
    }
    opt = pBoard->select_board(1);
    if (opt != std::nullopt) {
        pSelected = opt.value();
        pSelected->set_cell_owner(2, O);
    }
    opt = pBoard->select_board(2);
    if (opt != std::nullopt) {
        pSelected = opt.value();
        pSelected->set_cell_owner(2, X);
    }
    pBoard->mark_cell(2, pBoard->get_cell_owner(2));
    if (pBoard->check_win(2, X)) {
        victor = X;
    }
    factory->getNcHandler()->render();

    // while (victor == None) {
    // }

    return EXIT_SUCCESS;
}
