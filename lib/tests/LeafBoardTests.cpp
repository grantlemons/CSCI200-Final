/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "doctest.h"
#include "gsl/narrow"
#include "lib/board/LeafBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>

TEST_SUITE("Leaf Board Tests") {
    TEST_CASE("Test Cells Init") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *const P_board = factory->getLeafBoard(0);

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(P_board->get_cell_owner(i), NONE);
        }
    }
    TEST_CASE("Test Setting Cells") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *const P_board = factory->getLeafBoard(0);

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(P_board->get_cell_owner(i), NONE);

            P_board->set_cell_owner(i, X);
            CHECK_EQ(P_board->get_cell_owner(i), X);
        }
    }
}
