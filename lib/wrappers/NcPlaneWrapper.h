#ifndef NCPLANE_WRAPPER
#define NCPLANE_WRAPPER

#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcPlaneWrapper
 * Wrapper class around notcurses plane type.
 */
class NcPlaneWrapper : virtual public NcPlaneWrapperI {
private:
    ncplane *const _pPlane;
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
    NcPlaneWrapper(NcHandlerI *ncHandler, const int Y, const int X,
                   const int ROWS, const int COLS);

    /**
     * Constructor using dependency injection that takes the plane to wrap.
     *
     * @param PLANE The plane to wrap.
     * @param isStdPlane If the given plane is the stdplane.
     *
     * Changes destruction behavior.
     */
    NcPlaneWrapper(ncplane *const PLANE, const bool isStdPlane);

    /**
     * Constructor using an ncplane_options struct for options to construct.
     */
    NcPlaneWrapper(NcHandlerI *ncHandler, const ncplane_options NOPTS);

    /**
     * Copy constructor for wrapper.
     *
     * Uses `ncplane_dup()` to copy the underlying ncplane.
     */
    NcPlaneWrapper(NcPlaneWrapper &other);
    NcPlaneWrapper();
    ~NcPlaneWrapper();

    void dim_yx(int &ROWS, int &COLS) const override final;
    int get_rows() const override final;
    int get_cols() const override final;

    GraphicalAreaI *
    create_child(const ncplane_options *const nopts) override final;

    int load_nccell(nccell *const c, const char *const gcluster) override final;
    int set_base_cell(const nccell *const c) override final;

    int cursor_move_yx(const int X, const int Y) override final;

    /**
     * @copydoc GraphicalAreaI::hline()
     */
    int hline(const nccell *const c, const unsigned int LEN) override final;

    /**
     * @copydoc GraphicalAreaI::vline()
     */
    int vline(const nccell *const c, const unsigned int LEN) override final;
    int putc_yx(const int Y, const int X, const nccell *const c) override final;
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
    static ncplane_options create_nopts(const int Y, const int X,
                                        const unsigned int ROWS,
                                        const unsigned int COLS);

    /**
     * Extracts the configuration used to form the given plane.
     *
     * @param PLANE The plane to extract the configuration from.
     * @return An ncplane_options struct describing the plane's configuration
     * options.
     */
    static ncplane_options extract_nopts(ncplane *PLANE);
};

#endif
