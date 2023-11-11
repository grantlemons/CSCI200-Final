#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>

int main() {
    std::shared_ptr<NcHandler> ncHandler(new NcHandler());

    PrimaryBoard pBoard(ncHandler);
    pBoard.draw();

    LeafBoard *selected = nullptr;
    std::optional<LeafBoard *> opt = nullptr;

    opt = pBoard.select_board(2u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(0u, X);
    }
    opt = pBoard.select_board(0u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2u, O);
    }
    opt = pBoard.select_board(2u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(1u, X);
    }
    opt = pBoard.select_board(1u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2u, O);
    }
    opt = pBoard.select_board(2u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->set_cell_owner(2u, X);
    }
    ncHandler->render();

    while (1)
        ;

    delete selected;
    return EXIT_SUCCESS;
}
