#include "lib/graphical_board/PrimaryGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/GraphicalBoardA.h"
#include "lib/graphical_board/LeafGraphicalBoard.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler,
                                             int const Y, int const X,
                                             int const ROWS, int const COLS)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler,
                                             ncplane_options const NOPTS)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, NOPTS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(NcHandlerI *const P_ncHandler,
                                             NcPlaneWrapperI *const P_plane)
    : GraphicalBoardA::GraphicalBoardA{P_ncHandler, P_plane} {
    init_child_planes();
}

PrimaryGraphicalBoard::~PrimaryGraphicalBoard() {
    delete mprimaryPlane;
}

void PrimaryGraphicalBoard::init_child_planes() {
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
        auto *const P_newPlane =
            dynamic_cast<NcPlaneWrapperI *>(create_child(&childNopts));
        GraphicalAreaI *pTmp = new LeafGraphicalBoard{mncHandler, P_newPlane};

        mchildren.at(i) = std::unique_ptr<GraphicalAreaI>{pTmp};
    }
}

void PrimaryGraphicalBoard::draw_x(int const INDEX) {
    GraphicalBoardA::draw_x(INDEX);
    fill_x(INDEX);
}

void PrimaryGraphicalBoard::draw_o(int const INDEX) {
    GraphicalBoardA::draw_o(INDEX);
    fill_o(INDEX);
}

void PrimaryGraphicalBoard::fill_x(int const INDEX) {
    auto *const P_target{dynamic_cast<GraphicalBoardA *>(
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        GraphicalAreaI *const P_child = P_target->get_children().at(i);
        nccell const RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                        mncHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mncHandler->render();
}

void PrimaryGraphicalBoard::fill_o(int const INDEX) {
    GraphicalBoardA *const P_target{dynamic_cast<GraphicalBoardA *>(
        mchildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        GraphicalAreaI *const P_child = P_target->get_children().at(i);
        nccell const RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combine_channels(NcHandler::RED_CHANNEL,
                                        mncHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mncHandler->render();
}
