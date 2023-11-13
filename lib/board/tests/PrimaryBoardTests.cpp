#include "doctest.h"
#include "gsl/narrow"
#include "lib/GraphicalBoard.h"
#include "lib/Shared.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/dummies/GraphicalBoardDummy.h"
#include "lib/dummies/NcHandlerDummy.h"
#include "lib/interfaces/NcHandlerI.h"

#include <optional>

PrimaryBoard create_p_board();
PrimaryBoard create_p_board() {
    std::shared_ptr<NcHandlerI> handler{new NcHandlerDummy()};
    std::unique_ptr<GraphicalBoardI> gBoardDummy{new GraphicalBoardDummy()};

    return PrimaryBoard{handler, std::move(gBoardDummy)};
}

TEST_SUITE("Primary Board Tests") {
    TEST_CASE("Test Cells Init") {
        PrimaryBoard board = create_p_board();

        for (unsigned int i = 0; i < CELL_COUNT; i++) {
            CHECK_EQ(board.get_cell_owner(gsl::narrow<int>(i)), None);
        }
    }

    TEST_CASE("Test Select Leaf") {
        PrimaryBoard board = create_p_board();

        SUBCASE("Win Cell 0") {
            int LB_INDEX = 0;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Win Cell 1") {
            int LB_INDEX = 1;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Win Cell 2") {
            int LB_INDEX = 2;

            std::optional<LeafBoard *> selected = board.select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(board.get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Test Winning PrimaryBoard") {
            for (int i = 0; i < 3; i++) {
                std::optional<LeafBoard *> selected = board.select_board(i);
                REQUIRE_NE(selected, std::nullopt);

                for (int j = 0; j < 3; j++) {
                    selected.value()->set_cell_owner(j, X);
                    REQUIRE_EQ(selected.value()->get_cell_owner(j), X);
                }
            }
            CHECK(board.check_win(2, X));
        }
    }
}
