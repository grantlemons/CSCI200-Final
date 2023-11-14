#include "lib/wrappers/NcPlaneWrapper.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <cstdlib>
#include <notcurses/notcurses.h>

NcPlaneWrapper::NcPlaneWrapper(NcHandlerI *ncHandler, const int Y, const int X,
                               const int ROWS, const int COLS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncHandler, create_nopts(Y, X, gsl::narrow<unsigned int>(ROWS),
                                  gsl::narrow<unsigned int>(COLS))) {
    Expects(ROWS >= 0 && COLS >= 0);
}
NcPlaneWrapper::NcPlaneWrapper(NcHandlerI *ncHandler,
                               const ncplane_options NOPTS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncplane_create(ncHandler->get_stdplane(), &NOPTS), false) {}
NcPlaneWrapper::NcPlaneWrapper(ncplane *const PLANE, const bool isStdPlane)
    : _pPlane{PLANE}, _isStdPlane{isStdPlane} {}
NcPlaneWrapper::NcPlaneWrapper(NcPlaneWrapper &other)
    : _pPlane{ncplane_dup(other._pPlane, nullptr)},
      _isStdPlane{other._isStdPlane} {}

NcPlaneWrapper::~NcPlaneWrapper() {
    if (!_isStdPlane) {
        ncplane_erase(_pPlane);
    }
}

void NcPlaneWrapper::dim_yx(int &ROWS, int &COLS) const {
    unsigned int localRows, localCols;

    ncplane_dim_yx(_pPlane, &localRows, &localCols);

    ROWS = gsl::narrow<int>(localRows);
    COLS = gsl::narrow<int>(localCols);
}
int NcPlaneWrapper::get_rows() const {
    int res = gsl::narrow<int>(ncplane_dim_y(_pPlane));

    Ensures(res >= 0);

    return res;
}
int NcPlaneWrapper::get_cols() const {
    int res = gsl::narrow<int>(ncplane_dim_x(_pPlane));

    Ensures(res >= 0);

    return res;
}

GraphicalAreaI *NcPlaneWrapper::create_child(const ncplane_options *nopts) {
    return new NcPlaneWrapper{ncplane_create(_pPlane, nopts), false};
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
int NcPlaneWrapper::hline(const nccell *c, const unsigned int LEN) {
    return ncplane_hline(_pPlane, c, LEN);
}
int NcPlaneWrapper::vline(const nccell *c, const unsigned int LEN) {
    return ncplane_vline(_pPlane, c, LEN);
}
int NcPlaneWrapper::putc_yx(const int Y, const int X, const nccell *c) {
    return ncplane_putc_yx(_pPlane, Y, X, c);
}
void NcPlaneWrapper::erase() {
    return ncplane_erase(_pPlane);
}

ncplane_options NcPlaneWrapper::create_nopts(const int Y, const int X,
                                             const unsigned int ROWS,
                                             const unsigned int COLS) {
    ncplane_options nopts = {
        Y, X, ROWS, COLS, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}

ncplane_options NcPlaneWrapper::extract_nopts(ncplane *PLANE) {
    unsigned int rows, cols;
    ncplane_dim_yx(PLANE, &rows, &cols);

    int y, x;
    ncplane_yx(PLANE, &y, &x);

    ncplane_options nopts = {
        y, x, rows, cols, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}
