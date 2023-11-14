#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/BoardA.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/graphical_board/PrimaryGraphicalBoard.h"
#include "lib/interfaces/GraphicalBoardI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>

int main() {
    std::unique_ptr<NcHandlerI> ncHandler{new NcHandler{}};

    PrimaryBoard pBoard{ncHandler.get()};
    pBoard.draw();

    CellOwner victor = None;
    LeafBoard *selected = nullptr;
    std::optional<LeafBoard *> opt = nullptr;

    opt = pBoard.select_board(2);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(0, X);
    }
    opt = pBoard.select_board(0);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2, O);
    }
    opt = pBoard.select_board(2);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(1, X);
    }
    opt = pBoard.select_board(1);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2, O);
    }
    opt = pBoard.select_board(2);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2, X);
    }
    pBoard.mark_cell(2, pBoard.get_cell_owner(2));
    if (pBoard.check_win(2, X)) {
        victor = X;
    }
    ncHandler->render();

    while (victor == None) {}

    return EXIT_SUCCESS;
}
