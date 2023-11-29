#ifndef NCPLANE_WRAPPER_DUMMY
#define NCPLANE_WRAPPER_DUMMY

#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

/**
 * @class NcPlaneWrapperDummy
 * Dummy class used as a substitute for INcPlaneWrapper classes for testing
 * purposes.
 */
class NcPlaneWrapperDummy : public INcPlaneWrapper {
public:
    NcPlaneWrapperDummy() = default;

    void dim_yx(int &ROWS, int &COLS) const override final;
    [[nodiscard]] int get_rows() const override final;
    [[nodiscard]] int get_cols() const override final;

    INcPlaneWrapper *
    create_child(const ncplane_options *const P_nopts) override final;

    int load_nccell(nccell *const P_c,
                    const char *const P_gcluster) override final;
    int set_base_cell(const nccell *const P_c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *const P_c, const unsigned LEN) override final;
    int vline(const nccell *const P_c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X,
                const nccell *const P_c) override final;
    void erase() override final;
};

#endif
