#ifndef NCPLANE_WRAPPER_DUMMY
#define NCPLANE_WRAPPER_DUMMY

#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

/**
 * @class NcPlaneWrapperDummy
 * Dummy class used as a substitute for NcPlaneWrapperI classes for testing
 * purposes.
 */
class NcPlaneWrapperDummy : public NcPlaneWrapperI {
public:
    NcPlaneWrapperDummy();

    void dim_yx(int &ROWS, int &COLS) const override final;
    int get_rows() const override final;
    int get_cols() const override final;

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
