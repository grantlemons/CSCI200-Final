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
    ncplane *const P_PLANE;
    bool _isStdPlane;

public:
    /**
     * Constructor using the raw dimensions and location of the plane to
     * construct.
     *
     * @param P_ncHandler The handler object used to access the underlying
     * notcurses instance.
     * @param Y The Y coordinate of the new plane's top left corner.
     * @param X The X coordinate of the new plane's top left corner.
     * @param ROWS The number of rows composing the new plane. (Height)
     * @param COLS The number of columns composing the new plane. (Width)
     */
    NcPlaneWrapper(INcHandler *P_ncHandler, const int Y, const int X,
                   const int ROWS, const int COLS);

    /**
     * Constructor using dependency injection that takes the plane to wrap.
     *
     * @param P_plane The plane to wrap.
     * @param IS_STD_PLANE If the given plane is the stdplane.
     *
     * Changes destruction behavior.
     */
    NcPlaneWrapper(ncplane *const P_plane, const bool IS_STD_PLANE);

    /**
     * Constructor using an ncplane_options struct for options to construct.
     */
    NcPlaneWrapper(INcHandler *P_ncHandler, const ncplane_options NOPTS);

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
    create_child(const ncplane_options *const P_nopts) override final;

    int load_nccell(nccell *const P_c,
                    const char *const P_gcluster) override final;
    int set_base_cell(const nccell *const P_c) override final;

    int cursor_move_yx(const int X, const int Y) override final;

    /**
     * @copydoc IGraphicalArea::hline()
     */
    int hline(const nccell *const P_c, const unsigned int LEN) override final;

    /**
     * @copydoc IGraphicalArea::vline()
     */
    int vline(const nccell *const P_c, const unsigned int LEN) override final;
    int putc_yx(const int Y, const int X,
                const nccell *const P_c) override final;
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
    static ncplane_options createNopts(const int Y, const int X,
                                       const unsigned int ROWS,
                                       const unsigned int COLS);

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
