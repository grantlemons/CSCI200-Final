#include "AGraphicalBoardDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>
#include <notcurses/notcurses.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

AGraphicalBoardDummy::AGraphicalBoardDummy(
    std::shared_ptr<INcPlaneWrapper> plane)
    : _primaryPlane{std::move(plane)}, _children{} {}

std::shared_ptr<INcPlaneWrapper> AGraphicalBoardDummy::get_primary_plane() {
    return _primaryPlane;
}

void AGraphicalBoardDummy::set_children(
    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT> array) {
    _children = std::move(array);
}

void AGraphicalBoardDummy::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {}
void AGraphicalBoardDummy::draw_x(const int INDEX) {}
void AGraphicalBoardDummy::draw_o(const int INDEX) {}
void AGraphicalBoardDummy::draw_tie(const int INDEX) {}

std::array<IGraphicalArea *, CELL_COUNT> AGraphicalBoardDummy::get_children() {
    std::array<IGraphicalArea *, CELL_COUNT> planes{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        planes.at(i) = _children.at(i).get();
    }

    return planes;
}

// Inherited methods of INcPlaneWrapper
void AGraphicalBoardDummy::dim_yx(int &ROWS, int &COLS) const {
    _primaryPlane->dim_yx(ROWS, COLS);
}
int AGraphicalBoardDummy::get_rows() const {
    return _primaryPlane->get_rows();
}
int AGraphicalBoardDummy::get_cols() const {
    return _primaryPlane->get_cols();
}

IGraphicalArea *
AGraphicalBoardDummy::create_child(const ncplane_options *nopts) {
    return _primaryPlane->create_child(nopts);
}

int AGraphicalBoardDummy::load_nccell(nccell *const P_c, const char *gcluster) {
    return _primaryPlane->load_nccell(P_c, gcluster);
}
int AGraphicalBoardDummy::set_base_cell(const nccell *const P_c) {
    return _primaryPlane->set_base_cell(P_c);
}

int AGraphicalBoardDummy::cursor_move_yx(const int X, const int Y) {
    return _primaryPlane->cursor_move_yx(X, Y);
}
int AGraphicalBoardDummy::hline(const nccell *const P_c, const unsigned LEN) {
    return _primaryPlane->hline(P_c, LEN);
}
int AGraphicalBoardDummy::vline(const nccell *const P_c, const unsigned LEN) {
    return _primaryPlane->vline(P_c, LEN);
}
int AGraphicalBoardDummy::putc_yx(const int Y, const int X,
                                  const nccell *const P_c) {
    return _primaryPlane->putc_yx(Y, X, P_c);
}
void AGraphicalBoardDummy::erase() {
    _primaryPlane->erase();
}

#pragma GCC diagnostic pop
