#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/BoardA.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/dummies/GraphicalBoardDummy.h"
#include "lib/dummies/NcHandlerDummy.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/graphical_board/PrimaryGraphicalBoard.h"
#include "lib/interfaces/GraphicalBoardI.h"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>

int main() {
    std::shared_ptr<NcHandlerI> ncHandler{new NcHandlerDummy{}};
    NcPlaneWrapperI *stdPlane{new NcPlaneWrapperDummy{}};
    std::unique_ptr<GraphicalBoardI> gBoard{new GraphicalBoardDummy{stdPlane}};
    // std::unique_ptr<GraphicalBoardI> gBoard{
    //     new PrimaryGraphicalBoard{ncHandler.get(), stdPlane}};

    PrimaryBoard pBoard{ncHandler, std::move(gBoard)};
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

    // while (1);

    return EXIT_SUCCESS;
}
