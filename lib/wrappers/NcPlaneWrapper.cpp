#include "lib/wrappers/NcPlaneWrapper.h"

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <notcurses/notcurses.h>

NcPlaneWrapper::NcPlaneWrapper(NcHandlerI *ncHandler, const int Y, const int X,
                               const unsigned int ROWS, const unsigned int COLS)
    : NcPlaneWrapper::NcPlaneWrapper(ncHandler,
                                     create_nopts(Y, X, ROWS, COLS)) {}
NcPlaneWrapper::NcPlaneWrapper(NcHandlerI *ncHandler,
                               const ncplane_options NOPTS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncplane_create(ncHandler->get_stdplane(), &NOPTS)) {
    _isStdPlane = true;
}
NcPlaneWrapper::NcPlaneWrapper(ncplane *const PLANE)
    : _pPlane{PLANE}, _isStdPlane{false} {}
NcPlaneWrapper::NcPlaneWrapper(NcPlaneWrapper &other)
    : _pPlane{ncplane_dup(other._pPlane, nullptr)},
      _isStdPlane{other._isStdPlane} {}

NcPlaneWrapper::~NcPlaneWrapper() {
    if (!_isStdPlane) {
        ncplane_erase(_pPlane);
        free(_pPlane);
    }
}

void NcPlaneWrapper::dim_yx(unsigned int *const ROWS,
                            unsigned int *const COLS) const {
    ncplane_dim_yx(_pPlane, ROWS, COLS);
}
unsigned int NcPlaneWrapper::get_rows() const {
    return ncplane_dim_y(_pPlane);
}
unsigned int NcPlaneWrapper::get_cols() const {
    return ncplane_dim_x(_pPlane);
}

NcPlaneWrapperI *NcPlaneWrapper::create_child(const ncplane_options *nopts) {
    return new NcPlaneWrapper(ncplane_create(_pPlane, nopts));
}

int NcPlaneWrapper::load_nccell(nccell *c, const char *gcluster) {
    return nccell_load(_pPlane, c, gcluster);
}
int NcPlaneWrapper::set_base_cell(const nccell *c) {
    return ncplane_set_base_cell(_pPlane, c);
}

int NcPlaneWrapper::cursor_move_yx(const int X, const int Y) {
    return ncplane_cursor_move_yx(_pPlane, X, Y);
}
int NcPlaneWrapper::hline(const nccell *c, const unsigned LEN) {
    return ncplane_hline(_pPlane, c, LEN);
}
int NcPlaneWrapper::vline(const nccell *c, const unsigned LEN) {
    return ncplane_vline(_pPlane, c, LEN);
}
int NcPlaneWrapper::putc_yx(const int Y, const int X, const nccell *c) {
    return ncplane_putc_yx(_pPlane, Y, X, c);
}
void NcPlaneWrapper::erase() {
    return ncplane_erase(_pPlane);
}

// Helper functions
ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS) {
    ncplane_options nopts = {
        Y, X, ROWS, COLS, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}

ncplane_options extract_nopts(ncplane *PLANE) {
    unsigned int rows, cols;
    ncplane_dim_yx(PLANE, &rows, &cols);

    int y, x;
    ncplane_yx(PLANE, &y, &x);

    ncplane_options nopts = {
        y, x, rows, cols, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}
