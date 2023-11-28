#include "lib/graphical_board/PrimaryGraphicalBoard.h"

#include "gsl/narrow"
#include "lib/Shared.h"
#include "lib/graphical_board/AGraphicalBoard.h"
#include "lib/graphical_board/LeafGraphicalBoard.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

PrimaryGraphicalBoard::PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                                             const int Y, const int X,
                                             const int ROWS, const int COLS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, Y, X, ROWS, COLS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(INcHandler *const P_ncHandler,
                                             const ncplane_options NOPTS)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, NOPTS} {
    init_child_planes();
}

PrimaryGraphicalBoard::PrimaryGraphicalBoard(
    INcHandler *const P_ncHandler, std::unique_ptr<INcPlaneWrapper> P_plane)
    : AGraphicalBoard::AGraphicalBoard{P_ncHandler, std::move(P_plane)} {
    init_child_planes();
}

void PrimaryGraphicalBoard::init_child_planes() {
    const unsigned int ROWS_PER_BCELL =
        (gsl::narrow<unsigned int>(mRows) - 2u) / 3u;
    const unsigned int COLS_PER_BCELL =
        (gsl::narrow<unsigned int>(mCols) - 2u) / 3u;

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        const unsigned int COLUMN = i % 3u;
        const unsigned int ROW = (i - COLUMN) / 3u;

        const int NEW_Y = 1 + gsl::narrow<int>((ROWS_PER_BCELL * ROW));
        const int NEW_X = 1 + gsl::narrow<int>((COLS_PER_BCELL * COLUMN));

        const ncplane_options CHILD_NOPTS = NcPlaneWrapper::createNopts(
            NEW_Y, NEW_X, ROWS_PER_BCELL - 1u, COLS_PER_BCELL - 1u);
        auto newPlane = std::unique_ptr<INcPlaneWrapper>{
            dynamic_cast<INcPlaneWrapper *>(create_child(&CHILD_NOPTS))};
        IGraphicalArea *const P_tmp =
            new LeafGraphicalBoard{mNcHandler, std::move(newPlane)};

        mChildren.at(i) = std::unique_ptr<IGraphicalArea>{P_tmp};
    }
}

void PrimaryGraphicalBoard::draw_x(const int INDEX) {
    AGraphicalBoard::draw_x(INDEX);
    fill_x(INDEX);
}

void PrimaryGraphicalBoard::draw_o(const int INDEX) {
    AGraphicalBoard::draw_o(INDEX);
    fill_o(INDEX);
}

void PrimaryGraphicalBoard::fill_x(const int INDEX) {
    auto *const P_target{dynamic_cast<AGraphicalBoard *>(
        mChildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        IGraphicalArea *const P_child = P_target->get_children().at(i);
        const nccell RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                       mNcHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mNcHandler->render();
}

void PrimaryGraphicalBoard::fill_o(const int INDEX) {
    AGraphicalBoard *const P_target{dynamic_cast<AGraphicalBoard *>(
        mChildren.at(gsl::narrow<unsigned int>(INDEX)).get())};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        IGraphicalArea *const P_child = P_target->get_children().at(i);
        const nccell RED = NCCELL_INITIALIZER(
            '\0', 0,
            NcHandler::combineChannels(NcHandler::RED_CHANNEL,
                                       mNcHandler->get_default_fg_channel()));

        P_child->erase();
        P_child->set_base_cell(&RED);
    }

    // update the screen with the new changes
    mNcHandler->render();
}
