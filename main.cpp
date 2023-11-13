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
    std::shared_ptr<NcHandlerI> ncHandler(new NcHandler());

    PrimaryBoard pBoard(ncHandler);
    pBoard.draw();

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
    pBoard.check_win(2, X);
    ncHandler->render();

    while (1);

    return EXIT_SUCCESS;
}
