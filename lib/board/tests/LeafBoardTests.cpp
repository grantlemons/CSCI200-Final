#include "doctest.h"
#include "gsl/narrow"
#include "lib/board/LeafBoard.h"
#include "lib/dummies/GraphicalBoardDummy.h"
#include "lib/dummies/NcHandlerDummy.h"
#include "lib/interfaces/NcHandlerI.h"

#include <memory>

LeafBoard create_l_board();
LeafBoard create_l_board() {
    std::shared_ptr<NcHandlerI> handler{new NcHandlerDummy()};
    std::unique_ptr<GraphicalBoardI> gBoardDummy{new GraphicalBoardDummy()};

    return LeafBoard{handler, std::move(gBoardDummy)};
}

TEST_SUITE("Leaf Board Tests") {
    TEST_CASE("Test Cells Init") {
        LeafBoard board = create_l_board();

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(board.get_cell_owner(i), None);
        }
    }
    TEST_CASE("Test Setting Cells") {
        LeafBoard board = create_l_board();

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(board.get_cell_owner(i), None);

            board.set_cell_owner(i, X);
            CHECK_EQ(board.get_cell_owner(i), X);
        }
    }
}
