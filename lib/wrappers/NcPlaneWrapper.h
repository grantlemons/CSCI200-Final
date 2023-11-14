#ifndef NCPLANE_WRAPPER
#define NCPLANE_WRAPPER

#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcPlaneWrapper
 * Wrapper class around notcurses plane type.
 */
class NcPlaneWrapper : virtual public INcPlaneWrapper {
private:
    ncplane *const _P_plane;
    bool _isStdPlane;

public:
    /**
     * Constructor using the raw dimensions and location of the plane to
     * construct.
     *
     * @param ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     *
     * @see NcPlaneWrapper(NcHandlerI *, ncplane_options)
     */
    NcPlaneWrapper(INcHandler *P_cHandler, int const Y, int const X,
                   int const ROWS, int const COLS);

    /**
     * Constructor using dependency injection that takes the plane to wrap.
     *
     * @param PLANE The plane to wrap.
     * @param isStdPlane If the given plane is the stdplane.
     *
     * Changes destruction behavior.
     */
    NcPlaneWrapper(ncplane *const P_plane, bool const IS_STD_PLANE);

    /**
     * Constructor using an ncplane_options struct for options to construct.
     */
    NcPlaneWrapper(INcHandler *P_ncHandler, ncplane_options const NOPTS);

    /**
     * Copy constructor for wrapper.
     *
     * Uses `ncplane_dup()` to copy the underlying ncplane.
     */
    NcPlaneWrapper(NcPlaneWrapper &other);
    NcPlaneWrapper();
    ~NcPlaneWrapper() override;

    void dim_yx(int &ROWS, int &COLS) const override final;
    [[nodiscard]] int get_rows() const override final;
    [[nodiscard]] int get_cols() const override final;

    IGraphicalArea *
    create_child(ncplane_options const *const P_nopts) override final;

    int load_nccell(nccell *const P_c,
                    char const *const P_gcluster) override final;
    int set_base_cell(nccell const *const P_c) override final;

    int cursor_move_yx(int const X, int const Y) override final;

    /**
     * @copydoc GraphicalAreaI::hline()
     */
    int hline(nccell const *const P_c, unsigned int const LEN) override final;

    /**
     * @copydoc GraphicalAreaI::vline()
     */
    int vline(nccell const *const P_c, unsigned int const LEN) override final;
    int putc_yx(int const Y, int const X,
                nccell const *const P_c) override final;
    void erase() override final;

    /**
     * Forms an struct describing the configuration of a notcurses plane from
     * the data passed in.
     *
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     * @return An ncplane_options struct describing the configuration options.
     */
    static ncplane_options createNopts(int const Y, int const X,
                                       unsigned int const ROWS,
                                       unsigned int const COLS);

    /**
     * Extracts the configuration used to form the given plane.
     *
     * @param PLANE The plane to extract the configuration from.
     * @return An ncplane_options struct describing the plane's configuration
     * options.
     */
    static ncplane_options extractNopts(ncplane *PLANE);
};

#endif
