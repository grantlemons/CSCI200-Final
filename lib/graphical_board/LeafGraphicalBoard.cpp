#include "lib/graphical_board/LeafGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *const P_ncHandler,
                                       int const Y, int const X, int const ROWS,
                                       int const COLS)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *const P_ncHandler,
                                       ncplane_options const NOPTS)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, NOPTS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(NcHandlerI *const P_ncHandler,
                                       NcPlaneWrapperI *const P_plane)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, P_plane} {
    init_child_planes();
}

void LeafGraphicalBoard::init_child_planes() {
    unsigned int const ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(mrows) - 2u) / 3u;
    unsigned int const COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(mcols) - 2u) / 3u;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        unsigned int const COLUMN = i % 3u;
        unsigned int const ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options childNopts = NcPlaneWrapper::create_nopts(
            newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        GraphicalAreaI *pTmp = create_child(&childNopts);

        mchildren.at(i) = std::unique_ptr<GraphicalAreaI>{pTmp};
    }
}
