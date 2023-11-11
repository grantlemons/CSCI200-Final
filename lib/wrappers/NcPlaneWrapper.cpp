#include "lib/wrappers/NcPlaneWrapper.h"

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <notcurses/notcurses.h>

NcPlaneWrapper::NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                               const int Y, const int X,
                               const unsigned int ROWS, const unsigned int COLS)
    : NcPlaneWrapper::NcPlaneWrapper(ncHandler,
                                     create_nopts(Y, X, ROWS, COLS)) {}
NcPlaneWrapper::NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                               const ncplane_options NOPTS)
    : NcPlaneWrapper::NcPlaneWrapper(
          ncHandler, ncplane_create(ncHandler->get_stdplane(), &NOPTS)) {}
NcPlaneWrapper::NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                               ncplane *const PLANE)
    : _ncHandler(ncHandler), _pPlane(PLANE) {}
NcPlaneWrapper::NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                               NcPlaneWrapper &other)
    : _ncHandler(ncHandler), _pPlane(ncplane_dup(other._pPlane, nullptr)) {}

NcPlaneWrapper::~NcPlaneWrapper() {
    ncplane_erase(_pPlane);
    free(_pPlane);
}

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
