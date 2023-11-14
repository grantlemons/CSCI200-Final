#include "GraphicalBoardDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "lib/wrappers/NcPlaneWrapper.h"

#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

GraphicalBoardDummy::GraphicalBoardDummy(INcPlaneWrapper *const P_plane)
    : _primaryPlane{std::shared_ptr<INcPlaneWrapper>{P_plane}}, _children{} {
    init_child_planes();
}

GraphicalBoardDummy::GraphicalBoardDummy(std::shared_ptr<INcPlaneWrapper> plane)
    : _primaryPlane{plane}, _children{} {}

void GraphicalBoardDummy::init_child_planes() {
    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        _children.at(i) = std::unique_ptr<IGraphicalArea>{
            new GraphicalBoardDummy{_primaryPlane}};
    }
}

void GraphicalBoardDummy::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {}
void GraphicalBoardDummy::draw_x(const int INDEX) {}
void GraphicalBoardDummy::draw_o(const int INDEX) {}

std::array<IGraphicalArea *, CELL_COUNT> GraphicalBoardDummy::get_children() {
    std::array<IGraphicalArea *, CELL_COUNT> planes{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        planes.at(i) = _children.at(i).get();
    }

    return planes;
}

// Inherited methods of INcPlaneWrapper
void GraphicalBoardDummy::dim_yx(int &ROWS, int &COLS) const {
    _primaryPlane->dim_yx(ROWS, COLS);
}
int GraphicalBoardDummy::get_rows() const {
    return _primaryPlane->get_rows();
}
int GraphicalBoardDummy::get_cols() const {
    return _primaryPlane->get_cols();
}

IGraphicalArea *
GraphicalBoardDummy::create_child(const ncplane_options *nopts) {
    return _primaryPlane->create_child(nopts);
}

int GraphicalBoardDummy::load_nccell(nccell *const P_c, const char *gcluster) {
    return _primaryPlane->load_nccell(P_c, gcluster);
}
int GraphicalBoardDummy::set_base_cell(const nccell *const P_c) {
    return _primaryPlane->set_base_cell(P_c);
}

int GraphicalBoardDummy::cursor_move_yx(const int X, const int Y) {
    return _primaryPlane->cursor_move_yx(X, Y);
}
int GraphicalBoardDummy::hline(const nccell *const P_c, const unsigned LEN) {
    return _primaryPlane->hline(P_c, LEN);
}
int GraphicalBoardDummy::vline(const nccell *const P_c, const unsigned LEN) {
    return _primaryPlane->vline(P_c, LEN);
}
int GraphicalBoardDummy::putc_yx(const int Y, const int X,
                                 const nccell *const P_c) {
    return _primaryPlane->putc_yx(Y, X, P_c);
}
void GraphicalBoardDummy::erase() {
    _primaryPlane->erase();
}

#pragma GCC diagnostic pop
