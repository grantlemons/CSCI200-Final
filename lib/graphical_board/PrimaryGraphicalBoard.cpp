#include "lib/graphical_board/PrimaryGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/graphical_board/LeafGraphicalBoard.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const ncHandler,
                                             const int Y, const int X,
                                             const int ROWS, const int COLS)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const ncHandler,
                                             const ncplane_options NOPTS)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, NOPTS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const ncHandler,
                                             NcPlaneWrapperI *const PLANE)
    : GraphicalBoardA::GraphicalBoardA{ncHandler, PLANE} {
    init_child_planes();
}

PrimaryGraphicalBoard::~PrimaryGraphicalBoard() {
    delete _primaryPlane;
}

void PrimaryGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(_rows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(_cols) - 2u) / 3u;

    for (unsigned int i = 0; i < 9; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        int newY = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        int newX = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        ncplane_options child_nopts = NcPlaneWrapper::create_nopts(
            newY, newX, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        GraphicalAreaI *tmp = new LeafGraphicalBoard{_ncHandler, child_nopts};

        _children.at(i) = std::unique_ptr<GraphicalAreaI>{tmp};
    }
}
