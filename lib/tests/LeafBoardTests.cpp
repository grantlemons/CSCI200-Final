#include "doctest.h"
#include "gsl/narrow"
#include "lib/board/LeafBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/factories/DummyBoardFactory.h"

#include <memory>

TEST_SUITE("Leaf Board Tests") {
    TEST_CASE("Test Cells Init") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *board = factory->getLeafBoard(0);

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(board->get_cell_owner(i), None);
        }
    }
    TEST_CASE("Test Setting Cells") {
        std::unique_ptr<AbstractBoardFactory> factory{new DummyBoardFactory{}};
        LeafBoard *board = factory->getLeafBoard(0);

        for (int i = 0; i < gsl::narrow<int>(CELL_COUNT); i++) {
            REQUIRE_EQ(board->get_cell_owner(i), None);

            board->set_cell_owner(i, X);
            CHECK_EQ(board->get_cell_owner(i), X);
        }
    }
}
