#include "lib/graphical_board/LeafGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/interfaces/NcHandlerI.h"

#include <memory>
#include <notcurses/notcurses.h>

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *ncHandler, const int Y,
                                       const int X, const int ROWS,
                                       const int COLS)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, Y, X, ROWS, COLS} {}

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *ncHandler,
                                       const ncplane_options NOPTS)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, NOPTS} {}

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *ncHandler,
                                       std::shared_ptr<NcPlaneWrapperI> plane)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, plane} {}

void LeafGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(_rows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(_cols) - 2u) / 3u;

    for (unsigned int i = 0; i < 9; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options child_nopts =
            create_nopts(newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        GraphicalAreaI *tmp = create_child(&child_nopts);

        _children.at(i) = std::shared_ptr<GraphicalAreaI>{tmp};
    }
}
