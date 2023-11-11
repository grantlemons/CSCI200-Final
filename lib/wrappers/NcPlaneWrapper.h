#ifndef NCPLANE_WRAPPER
#define NCPLANE_WRAPPER

#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

class NcPlaneWrapper : public NcPlaneWrapperI {
private:
    std::shared_ptr<NcHandlerI> _ncHandler;
    ncplane *const _pPlane;

public:
    NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler, const int Y,
                   const int X, const unsigned int ROWS,
                   const unsigned int COLS);
    NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                   const ncplane_options NOPTS);
    NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler, ncplane *const PLANE);
    NcPlaneWrapper(std::shared_ptr<NcHandlerI> ncHandler,
                   NcPlaneWrapper &other);
    ~NcPlaneWrapper();

    unsigned int get_rows() override final;
    unsigned int get_cols() override final;

    NcPlaneWrapperI *create_child(const ncplane_options *nopts) override final;

    int nccell_load(nccell *c, const char *gcluster) override final;
    int set_base_cell(const nccell *c) override final;

    int cursor_move_yx(const int X, const int Y) override final;
    int hline(const nccell *c, const unsigned LEN) override final;
    int vline(const nccell *c, const unsigned LEN) override final;
    int putc_yx(const int Y, const int X, const nccell *c) override final;
    int erase() override final;
};

// Helper functions

/**
 * Forms an struct describing the configuration of a notcurses plane from the
 * data passed in.
 *
 * @param Y The Y coordinate of the new plane's top left corner.
 * @param X The X coordinate of the new plane's top left corner.
 * @param ROWS The number of rows composing the new plane. (Height)
 * @param COLS The number of columns composing the new plane. (Width)
 * @return An ncplane_options struct describing the configuration options.
 */
ncplane_options create_nopts(const int Y, const int X, const unsigned int ROWS,
                             const unsigned int COLS);

/**
 * Extracts the configuration used to form the given plane.
 *
 * @param PLANE The plane to extract the configuration from.
 * @return An ncplane_options struct describing the plane's configuration
 * options.
 */
ncplane_options extract_nopts(ncplane *PLANE);

#endif
