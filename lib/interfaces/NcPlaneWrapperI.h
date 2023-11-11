#ifndef NCPLANE_WRAPPERI
#define NCPLANE_WRAPPERI

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <notcurses/notcurses.h>

class NcPlaneWrapperI {
public:
    virtual unsigned int get_rows() = 0;
    virtual unsigned int get_cols() = 0;

    virtual NcPlaneWrapperI *create_child(const ncplane_options *nopts) = 0;

    virtual int nccell_load(nccell *c, const char *gcluster) = 0;
    virtual int set_base_cell(const nccell *c) = 0;

    virtual int cursor_move_yx(const int X, const int Y) = 0;
    virtual int hline(const nccell *c, const unsigned LEN) = 0;
    virtual int vline(const nccell *c, const unsigned LEN) = 0;
    virtual int putc_yx(const int Y, const int X, const nccell *c) = 0;
    virtual int erase() = 0;
};

#endif
