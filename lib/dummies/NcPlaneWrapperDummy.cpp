#include "lib/dummies/NcPlaneWrapperDummy.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

// NcPlaneWrapperDummy::

NcPlaneWrapperDummy::NcPlaneWrapperDummy() {}

void NcPlaneWrapperDummy::dim_yx(int &ROWS, int &COLS) const {
    ROWS = 1;
    COLS = 1;
}
int NcPlaneWrapperDummy::get_rows() const {
    return 1;
}
int NcPlaneWrapperDummy::get_cols() const {
    return 1;
}

NcPlaneWrapperI *
NcPlaneWrapperDummy::create_child(const ncplane_options *const nopts) {
    return new NcPlaneWrapperDummy();
}

int NcPlaneWrapperDummy::load_nccell(nccell *const c,
                                     const char *const gcluster) {
    return 0;
}
int NcPlaneWrapperDummy::set_base_cell(const nccell *const c) {
    return 0;
}

int NcPlaneWrapperDummy::cursor_move_yx(const int X, const int Y) {
    return 0;
}
int NcPlaneWrapperDummy::hline(const nccell *const c, const unsigned LEN) {
    return 0;
}
int NcPlaneWrapperDummy::vline(const nccell *const c, const unsigned LEN) {
    return 0;
}
int NcPlaneWrapperDummy::putc_yx(const int Y, const int X,
                                 const nccell *const c) {
    return 0;
}
void NcPlaneWrapperDummy::erase() {}

#pragma GCC diagnostic pop
