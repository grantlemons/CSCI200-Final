#include "doctest.h"
#include "lib/NcHandler.h"
#include "lib/board/Board.h"
#include "lib/board/LeafBoard.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/NcHandlerI.h"

LeafBoard create_board();
LeafBoard create_board() {
    std::shared_ptr<NcHandlerI> handler{new NcHandler()};
    std::unique_ptr<NcPlaneWrapperI> planeWrapper{new NcPlaneWrapperDummy()};

    return LeafBoard{handler, std::move(planeWrapper)};
}

TEST_SUITE("Board CheckWin Tests") {
    TEST_CASE("Check Win Horizontal") {
        LeafBoard board = create_board();

        SUBCASE("No Win Row 1") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(1, X);

            CHECK_FALSE(board.check_win(1, X));

            // Reset state
            board.set_cell_owner(0, None);
            board.set_cell_owner(1, None);
        }
        SUBCASE("No Win Row 2") {
            board.set_cell_owner(3, X);
            board.set_cell_owner(4, X);

            CHECK_FALSE(board.check_win(4, X));

            // Reset state
            board.set_cell_owner(3, None);
            board.set_cell_owner(4, None);
        }
        SUBCASE("No Win Row 3") {
            board.set_cell_owner(6, X);
            board.set_cell_owner(7, X);

            CHECK_FALSE(board.check_win(7, X));

            // Reset state
            board.set_cell_owner(6, None);
            board.set_cell_owner(7, None);
        }
        SUBCASE("Win Row 1") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(1, X);
            board.set_cell_owner(2, X);

            CHECK(board.check_win(3, X));

            // Reset state
            board.set_cell_owner(0, None);
            board.set_cell_owner(1, None);
            board.set_cell_owner(2, None);
        }
        SUBCASE("Win Row 2") {
            board.set_cell_owner(3, X);
            board.set_cell_owner(4, X);
            board.set_cell_owner(5, X);

            CHECK(board.check_win(6, X));

            // Reset state
            board.set_cell_owner(3, None);
            board.set_cell_owner(4, None);
            board.set_cell_owner(5, None);
        }
        SUBCASE("No Win Row 3") {
            board.set_cell_owner(6, X);
            board.set_cell_owner(7, X);
            board.set_cell_owner(8, X);

            CHECK(board.check_win(8, X));

            // Reset state
            board.set_cell_owner(6, None);
            board.set_cell_owner(7, None);
            board.set_cell_owner(8, None);
        }
    }

    TEST_CASE("Check Win Vertical") {
        LeafBoard board = create_board();

        SUBCASE("No Win Column 1") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(3, X);

            CHECK_FALSE(board.check_win(3, X));

            // Reset state
            board.set_cell_owner(0, None);
            board.set_cell_owner(3, None);
        }
        SUBCASE("No Win Column 2") {
            board.set_cell_owner(1, X);
            board.set_cell_owner(4, X);

            CHECK_FALSE(board.check_win(4, X));

            // Reset state
            board.set_cell_owner(1, None);
            board.set_cell_owner(4, None);
        }
        SUBCASE("No Win Column 3") {
            board.set_cell_owner(2, X);
            board.set_cell_owner(5, X);

            CHECK_FALSE(board.check_win(5, X));

            // Reset state
            board.set_cell_owner(2, None);
            board.set_cell_owner(5, None);
        }
        SUBCASE("Win Column 1") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(3, X);
            board.set_cell_owner(6, X);

            CHECK(board.check_win(6, X));

            // Reset state
            board.set_cell_owner(0, None);
            board.set_cell_owner(3, None);
            board.set_cell_owner(6, None);
        }
        SUBCASE("Win Column 2") {
            board.set_cell_owner(1, X);
            board.set_cell_owner(4, X);
            board.set_cell_owner(7, X);

            CHECK(board.check_win(7, X));

            // Reset state
            board.set_cell_owner(1, None);
            board.set_cell_owner(4, None);
            board.set_cell_owner(7, None);
        }
        SUBCASE("No Win Column 3") {
            board.set_cell_owner(2, X);
            board.set_cell_owner(5, X);
            board.set_cell_owner(8, X);

            CHECK(board.check_win(8, X));

            // Reset state
            board.set_cell_owner(2, None);
            board.set_cell_owner(5, None);
            board.set_cell_owner(8, None);
        }
    }

    TEST_CASE("Check Win Diagonal") {
        LeafBoard board = create_board();

        SUBCASE("No Win Twos") {
            board.set_cell_owner(2, X);
            board.set_cell_owner(6, X);

            CHECK_FALSE(board.check_win(6, X));

            board.set_cell_owner(2, None);
            board.set_cell_owner(6, None);
        }
        SUBCASE("Win Twos") {
            board.set_cell_owner(2, X);
            board.set_cell_owner(6, X);
            board.set_cell_owner(4, X);

            CHECK(board.check_win(4, X));

            board.set_cell_owner(2, None);
            board.set_cell_owner(6, None);
            board.set_cell_owner(4, None);
        }

        SUBCASE("No Win Fours") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(8, X);

            CHECK_FALSE(board.check_win(8, X));

            board.set_cell_owner(0, None);
            board.set_cell_owner(8, None);
        }
        SUBCASE("Win Fours") {
            board.set_cell_owner(0, X);
            board.set_cell_owner(8, X);
            board.set_cell_owner(4, X);

            CHECK_FALSE(board.check_win(4, X));

            board.set_cell_owner(0, None);
            board.set_cell_owner(8, None);
            board.set_cell_owner(4, None);
        }
    }
}
