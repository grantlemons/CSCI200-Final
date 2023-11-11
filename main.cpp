#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"

#include <cstdint>
#include <memory>
#include <optional>

int main() {
    std::shared_ptr<NcHandler> ncHandler(new NcHandler());

    PrimaryBoard pBoard(ncHandler);
    pBoard.draw();

    LeafBoard *selected = nullptr;
    std::optional<LeafBoard *> opt = pBoard.select_board(2u);
    if (opt != std::nullopt) {
        selected = opt.value();
        selected->draw_x(1);
        selected->draw_o(4);
    }
    pBoard.draw_o(0);
    pBoard.draw_x(3);
    ncHandler->render();

    while (1)
        ;

    return EXIT_SUCCESS;
}
