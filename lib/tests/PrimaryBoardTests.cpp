#include "doctest.h"
#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <optional>

TEST_SUITE("Primary Board Tests") {
    TEST_CASE("Test Cells Init") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        PrimaryBoard *const P_board = factory->getPrimaryBoard();

        for (unsigned int i = 0; i < CELL_COUNT; i++) {
            CHECK_EQ(P_board->get_cell_owner(gsl::narrow<int>(i)), NONE);
        }
    }

    TEST_CASE("Test Select Leaf") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        PrimaryBoard *const P_board = factory->getPrimaryBoard();

        SUBCASE("Win Cell 0") {
            const int LB_INDEX = 0;

            std::optional<LeafBoard *> selected =
                P_board->select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(P_board->get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Win Cell 1") {
            const int LB_INDEX = 1;

            std::optional<LeafBoard *> selected =
                P_board->select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(P_board->get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Win Cell 2") {
            const int LB_INDEX = 2;

            std::optional<LeafBoard *> selected =
                P_board->select_board(LB_INDEX);
            REQUIRE_NE(selected, std::nullopt);

            for (int i = 0; i < 3; i++) {
                selected.value()->set_cell_owner(i, X);
                REQUIRE_EQ(selected.value()->get_cell_owner(i), X);
            }

            CHECK_EQ(P_board->get_cell_owner(LB_INDEX), X);
        }
        SUBCASE("Test Winning PrimaryBoard") {
            for (int i = 0; i < 3; i++) {
                std::optional<LeafBoard *> selected = P_board->select_board(i);
                REQUIRE_NE(selected, std::nullopt);

                for (int j = 0; j < 3; j++) {
                    selected.value()->set_cell_owner(j, X);
                    REQUIRE_EQ(selected.value()->get_cell_owner(j), X);
                }
            }
            CHECK(P_board->check_win(2, X));
        }
    }
}
