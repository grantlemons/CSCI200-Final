#include "lib/graphical_board/LeafGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       const int Y, const int X, const int ROWS,
                                       const int COLS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, NOPTS} {
    init_child_planes();
}

LeafGraphicalBoard::LeafGraphicalBoard(INcHandler *const P_ncHandler,
                                       INcPlaneWrapper *const P_plane)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, P_plane} {
    init_child_planes();
}

void LeafGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(mrows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(mcols) - 2u) / 3u;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options childNopts = NcPlaneWrapper::createNopts(
            newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        IGraphicalArea *pTmp = create_child(&childNopts);

        mchildren.at(i) = std::unique_ptr<IGraphicalArea>{pTmp};
    }
}
