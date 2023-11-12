#include "doctest.h"
#include "lib/GraphicalBoard.h"
#include "lib/Shared.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/dummies/GraphicalBoardDummy.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <optional>

PrimaryBoard create_p_board();
PrimaryBoard create_p_board() {
    std::shared_ptr<NcHandlerI> handler{new NcHandler()};
    std::unique_ptr<GraphicalBoardI> gBoard{new GraphicalBoardDummy()};

    return PrimaryBoard{handler, std::move(gBoard)};
}

TEST_SUITE("Primary Board Tests") {
    TEST_CASE("Test Cells Init") {
        PrimaryBoard board = create_p_board();

        for (unsigned int i = 0; i < CELL_COUNT; i++) {
            CHECK_EQ(board.get_cell_owner(i), None);
        }
    }

    TEST_CASE("Test Select Leaf") {
        PrimaryBoard board = create_p_board();

        SUBCASE("Win Cell 0") {
            unsigned int LB_INDEX = 0;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            CHECK_NE(selected, std::nullopt);

            for (unsigned int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Win Cell 1") {
            unsigned int LB_INDEX = 1;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            CHECK_NE(selected, std::nullopt);

            for (unsigned int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }

        CHECK_FALSE(board.check_win(1, X));
        CHECK_FALSE(board.check_win(1, O));

        SUBCASE("Win Cell 2") {
            unsigned int LB_INDEX = 2;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            CHECK_NE(selected, std::nullopt);

            for (unsigned int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }

        CHECK(board.check_win(2, X));
        CHECK_FALSE(board.check_win(2, O));
    }
}
