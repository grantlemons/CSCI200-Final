#include "lib/dummies/NcPlaneWrapperDummy.h"

#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

// NcPlaneWrapperDummy::

NcPlaneWrapperDummy::NcPlaneWrapperDummy() {}

void NcPlaneWrapperDummy::dim_yx(unsigned int *const ROWS,
                                 unsigned int *const COLS) const {
    std::cout << "NC_PW_DUMMY: dim_yx called" << std::endl;
}
unsigned int NcPlaneWrapperDummy::get_rows() const {
    std::cout << "NC_PW_DUMMY: get_rows called" << std::endl;
    return 0;
}
unsigned int NcPlaneWrapperDummy::get_cols() const {
    std::cout << "NC_PW_DUMMY: get_cols called" << std::endl;
    return 0;
}

NcPlaneWrapperI *
NcPlaneWrapperDummy::create_child(const ncplane_options *const nopts) {
    std::cout << "NC_PW_DUMMY: create_child called" << std::endl;
    return new NcPlaneWrapperDummy();
}

int NcPlaneWrapperDummy::load_nccell(nccell *const c,
                                     const char *const gcluster) {
    std::cout << "NC_PW_DUMMY: load_nccell called" << std::endl;
    return 0;
}
int NcPlaneWrapperDummy::set_base_cell(const nccell *const c) {
    std::cout << "NC_PW_DUMMY: set_base_cell called" << std::endl;
    return 0;
}

int NcPlaneWrapperDummy::cursor_move_yx(const int X, const int Y) {
    std::cout << "NC_PW_DUMMY: cursor_move_yx called" << std::endl;
    return 0;
}
int NcPlaneWrapperDummy::hline(const nccell *const c, const unsigned LEN) {
    std::cout << "NC_PW_DUMMY: hline called" << std::endl;
    return 0;
}
int NcPlaneWrapperDummy::vline(const nccell *const c, const unsigned LEN) {
    std::cout << "NC_PW_DUMMY: vline called" << std::endl;
    return 0;
}
int NcPlaneWrapperDummy::putc_yx(const int Y, const int X,
                                 const nccell *const c) {
    std::cout << "NC_PW_DUMMY: putc_yx called" << std::endl;
    return 0;
}
void NcPlaneWrapperDummy::erase() {
    std::cout << "NC_PW_DUMMY: erase called" << std::endl;
}

#pragma GCC diagnostic pop
