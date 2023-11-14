#include "lib/wrappers/NcPlaneWrapper.h"

#include "gsl/assert"
#include "gsl/narrow"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"

#include <cstdint>
#include <cstdlib>
#include <notcurses/notcurses.h>

NcPlaneWrapper::NcPlaneWrapper(INcHandler *P_ncHandler, const int Y,
                               const int X, const int ROWS, const int COLS)
    : NcPlaneWrapper::NcPlaneWrapper(
          P_ncHandler, createNopts(Y, X, gsl::narrow<unsigned int>(ROWS),
                                   gsl::narrow<unsigned int>(COLS))) {
    Expects(ROWS >= 0 && COLS >= 0);
}
NcPlaneWrapper::NcPlaneWrapper(INcHandler *P_ncHandler,
                               const ncplane_options NOPTS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncplane_create(P_ncHandler->get_stdplane(), &NOPTS), false) {}
NcPlaneWrapper::NcPlaneWrapper(ncplane *const P_plane, const bool IS_STD_PLANE)
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
    const int RESULT = gsl::narrow<int>(ncplane_dim_y(_P_plane));

    Ensures(RESULT >= 0);

    return RESULT;
}
int NcPlaneWrapper::get_cols() const {
    const int RESULT = gsl::narrow<int>(ncplane_dim_x(_P_plane));

    Ensures(RESULT >= 0);

    return RESULT;
}

IGraphicalArea *NcPlaneWrapper::create_child(const ncplane_options *nopts) {
    return new NcPlaneWrapper{ncplane_create(_P_plane, nopts), false};
}

int NcPlaneWrapper::load_nccell(nccell *c, const char *gcluster) {
    return nccell_load(_P_plane, c, gcluster);
}
int NcPlaneWrapper::set_base_cell(const nccell *c) {
    return ncplane_set_base_cell(_P_plane, c);
}

int NcPlaneWrapper::cursor_move_yx(const int X, const int Y) {
    return ncplane_cursor_move_yx(_P_plane, X, Y);
}
int NcPlaneWrapper::hline(const nccell *c, const unsigned int LEN) {
    return ncplane_hline(_P_plane, c, LEN);
}
int NcPlaneWrapper::vline(const nccell *c, const unsigned int LEN) {
    return ncplane_vline(_P_plane, c, LEN);
}
int NcPlaneWrapper::putc_yx(const int Y, const int X, const nccell *c) {
    return ncplane_putc_yx(_P_plane, Y, X, c);
}
void NcPlaneWrapper::erase() {
    return ncplane_erase(_P_plane);
}

ncplane_options NcPlaneWrapper::createNopts(const int Y, const int X,
                                            const unsigned int ROWS,
                                            const unsigned int COLS) {
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
