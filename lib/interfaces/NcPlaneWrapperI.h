#ifndef NCPLANE_WRAPPERI
#define NCPLANE_WRAPPERI

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

class NcPlaneWrapperI {
public:
    virtual ~NcPlaneWrapperI() = default;

    virtual void dim_yx(int &ROWS, int &COLS) const = 0;
    virtual int get_rows() const = 0;
    virtual int get_cols() const = 0;

    virtual NcPlaneWrapperI *create_child(const ncplane_options *nopts) = 0;

    virtual int load_nccell(nccell *const c, const char *gcluster) = 0;
    virtual int set_base_cell(const nccell *const c) = 0;

    virtual int cursor_move_yx(const int X, const int Y) = 0;
    virtual int hline(const nccell *const c, const unsigned LEN) = 0;
    virtual int vline(const nccell *const c, const unsigned LEN) = 0;
    virtual int putc_yx(const int Y, const int X, const nccell *const c) = 0;
    virtual void erase() = 0;
};

#endif
