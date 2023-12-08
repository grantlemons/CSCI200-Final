/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "doctest.h"
#include "lib/board/ABoard.h"
#include "lib/board/LeafBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>

TEST_SUITE("Board CheckWin Tests") {
    TEST_CASE("Check Win Horizontal") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *const P_board = factory->getLeafBoard(0);

        SUBCASE("No Win Row 1") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(1, X);

            REQUIRE_EQ(P_board->get_cell_owner(2), NONE);
            CHECK_FALSE(P_board->check_win(1, X));
        }
        SUBCASE("No Win Row 2") {
            P_board->set_cell_owner(3, X);
            P_board->set_cell_owner(4, X);

            REQUIRE_EQ(P_board->get_cell_owner(5), NONE);
            CHECK_FALSE(P_board->check_win(4, X));
        }
        SUBCASE("No Win Row 3") {
            P_board->set_cell_owner(6, X);
            P_board->set_cell_owner(7, X);

            REQUIRE_EQ(P_board->get_cell_owner(8), NONE);
            CHECK_FALSE(P_board->check_win(7, X));
        }
        SUBCASE("Win Row 1") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(1, X);
            P_board->set_cell_owner(2, X);

            CHECK(P_board->check_win(2, X));
        }
        SUBCASE("Win Row 2") {
            P_board->set_cell_owner(3, X);
            P_board->set_cell_owner(4, X);
            P_board->set_cell_owner(5, X);

            CHECK(P_board->check_win(5, X));
        }
        SUBCASE("Win Row 3") {
            P_board->set_cell_owner(6, X);
            P_board->set_cell_owner(7, X);
            P_board->set_cell_owner(8, X);

            CHECK(P_board->check_win(8, X));
        }
    }

    TEST_CASE("Check Win Vertical") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *const P_board = factory->getLeafBoard(0);

        SUBCASE("No Win Column 1") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(3, X);

            REQUIRE_EQ(P_board->get_cell_owner(6), NONE);
            CHECK_FALSE(P_board->check_win(3, X));
        }
        SUBCASE("No Win Column 2") {
            P_board->set_cell_owner(1, X);
            P_board->set_cell_owner(4, X);

            REQUIRE_EQ(P_board->get_cell_owner(7), NONE);
            CHECK_FALSE(P_board->check_win(4, X));
        }
        SUBCASE("No Win Column 3") {
            P_board->set_cell_owner(2, X);
            P_board->set_cell_owner(5, X);

            REQUIRE_EQ(P_board->get_cell_owner(8), NONE);
            CHECK_FALSE(P_board->check_win(5, X));
        }
        SUBCASE("Win Column 1") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(3, X);
            P_board->set_cell_owner(6, X);

            CHECK(P_board->check_win(6, X));
        }
        SUBCASE("Win Column 2") {
            P_board->set_cell_owner(1, X);
            P_board->set_cell_owner(4, X);
            P_board->set_cell_owner(7, X);

            CHECK(P_board->check_win(7, X));
        }
        SUBCASE("Win Column 3") {
            P_board->set_cell_owner(2, X);
            P_board->set_cell_owner(5, X);
            P_board->set_cell_owner(8, X);

            CHECK(P_board->check_win(8, X));
        }
    }

    TEST_CASE("Check Win Diagonal") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *const P_board = factory->getLeafBoard(0);

        SUBCASE("No Win Twos") {
            P_board->set_cell_owner(2, X);
            P_board->set_cell_owner(6, X);

            REQUIRE_EQ(P_board->get_cell_owner(4), NONE);
            CHECK_FALSE(P_board->check_win(6, X));
        }
        SUBCASE("Win Twos") {
            P_board->set_cell_owner(2, X);
            P_board->set_cell_owner(6, X);
            P_board->set_cell_owner(4, X);

            CHECK(P_board->check_win(4, X));
        }

        SUBCASE("No Win Fours") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(8, X);

            REQUIRE_EQ(P_board->get_cell_owner(4), NONE);
            CHECK_FALSE(P_board->check_win(8, X));
        }
        SUBCASE("Win Fours") {
            P_board->set_cell_owner(0, X);
            P_board->set_cell_owner(8, X);
            P_board->set_cell_owner(4, X);

            CHECK(P_board->check_win(4, X));
        }
    }
}
