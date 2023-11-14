#include "lib/wrappers/NcPlaneWrapper.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"

#include <cstdint>
#include <cstdlib>
#include <notcurses/notcurses.h>

NcPlaneWrapper::NcPlaneWrapper(INcHandler *P_ncHandler, int const Y,
                               int const X, int const ROWS, int const COLS)
    : NcPlaneWrapper::NcPlaneWrapper(
          P_ncHandler, createNopts(Y, X, gsl::narrow<unsigned int>(ROWS),
                                   gsl::narrow<unsigned int>(COLS))) {
    Expects(ROWS >= 0 && COLS >= 0);
}
NcPlaneWrapper::NcPlaneWrapper(INcHandler *P_ncHandler,
                               ncplane_options const NOPTS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncplane_create(P_ncHandler->get_stdplane(), &NOPTS), false) {}
NcPlaneWrapper::NcPlaneWrapper(ncplane *const P_plane, bool const IS_STD_PLANE)
    : _P_plane{P_plane}, _isStdPlane{IS_STD_PLANE} {}
NcPlaneWrapper::NcPlaneWrapper(NcPlaneWrapper &other)
    : _P_plane{ncplane_dup(other._P_plane, nullptr)},
      _isStdPlane{other._isStdPlane} {}

NcPlaneWrapper::~NcPlaneWrapper() {
    if (!_isStdPlane) {
        ncplane_erase(_P_plane);
    }
}

void NcPlaneWrapper::dim_yx(int &ROWS, int &COLS) const {
    unsigned int localRows{0}, localCols{0};

    ncplane_dim_yx(_P_plane, &localRows, &localCols);

    ROWS = gsl::narrow<int>(localRows);
    COLS = gsl::narrow<int>(localCols);
}
int NcPlaneWrapper::get_rows() const {
    int res = gsl::narrow<int>(ncplane_dim_y(_P_plane));

    Ensures(res >= 0);

    return res;
}
int NcPlaneWrapper::get_cols() const {
    int res = gsl::narrow<int>(ncplane_dim_x(_P_plane));

    Ensures(res >= 0);

    return res;
}

IGraphicalArea *NcPlaneWrapper::create_child(ncplane_options const *nopts) {
    return new NcPlaneWrapper{ncplane_create(_P_plane, nopts), false};
}

int NcPlaneWrapper::load_nccell(nccell *c, char const *gcluster) {
    return nccell_load(_P_plane, c, gcluster);
}
int NcPlaneWrapper::set_base_cell(nccell const *c) {
    return ncplane_set_base_cell(_P_plane, c);
}

int NcPlaneWrapper::cursor_move_yx(int const X, int const Y) {
    return ncplane_cursor_move_yx(_P_plane, X, Y);
}
int NcPlaneWrapper::hline(nccell const *c, unsigned int const LEN) {
    return ncplane_hline(_P_plane, c, LEN);
}
int NcPlaneWrapper::vline(nccell const *c, unsigned int const LEN) {
    return ncplane_vline(_P_plane, c, LEN);
}
int NcPlaneWrapper::putc_yx(int const Y, int const X, nccell const *c) {
    return ncplane_putc_yx(_P_plane, Y, X, c);
}
void NcPlaneWrapper::erase() {
    return ncplane_erase(_P_plane);
}

ncplane_options NcPlaneWrapper::createNopts(int const Y, int const X,
                                            unsigned int const ROWS,
                                            unsigned int const COLS) {
    ncplane_options nopts = {
        Y, X, ROWS, COLS, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}

ncplane_options NcPlaneWrapper::extractNopts(ncplane *PLANE) {
    unsigned int rows{0}, cols{0};
    ncplane_dim_yx(PLANE, &rows, &cols);

    int y{0}, x{0};
    ncplane_yx(PLANE, &y, &x);

    ncplane_options nopts = {
        y, x, rows, cols, nullptr, nullptr, nullptr, 0, 0, 0,
    };

    return nopts;
}
