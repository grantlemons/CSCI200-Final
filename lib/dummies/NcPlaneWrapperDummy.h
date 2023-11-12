#ifndef NCPLANE_WRAPPER_DUMMY
#define NCPLANE_WRAPPER_DUMMY

#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

class NcPlaneWrapperDummy : public NcPlaneWrapperI {
public:
    NcPlaneWrapperDummy();

    void dim_yx(unsigned int *const ROWS,
                unsigned int *const COLS) const override final;
    unsigned int get_rows() const override final;
    unsigned int get_cols() const override final;

    NcPlaneWrapperI *
    create_child(const ncplane_options *const nopts) override final;

    int load_nccell(nccell *const c, const char *const gcluster) override final;
    int set_base_cell(const nccell *const c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const c, const unsigned LEN) override final;
    int vline(const nccell *const c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X, const nccell *const c) override final;
    void erase() override final;
};

#endif
