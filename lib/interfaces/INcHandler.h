#ifndef NC_HANDLERI
#define NC_HANDLERI

#include <cstdint>
#include <notcurses/notcurses.h>

// Forward declaration to avoid recursive includes
class INcPlaneWrapper;

/**
 * @class INcHandler
 * Interface for NcHandler classes.
 *
 * @see NcHandler
 * @see NcHandlerDummy
 */
class INcHandler {
public:
    virtual ~INcHandler() = default;

    /**
     * Getter for notcurses stdplane.
     * Should not be used explicitly, prefer `get_stdplane_wrapper()`.
     *
     * @return The stdplane for the notcurses instance.
     *
     * @see get_stdplane_wrapper()
     */
    [[nodiscard]] virtual ncplane *get_stdplane() const = 0;

    /**
     * Getter for wrapper object of stdplane.
     *
     * @return Wrapper around notcurses instance stdplane.
     *
     * @see get_stdplane()
     */
    [[nodiscard]] virtual INcPlaneWrapper *get_stdplane_wrapper() const = 0;

    /**
     * Gets default background color channel from the stdplane.
     *
     * @return The default background color channel.
     */
    [[nodiscard]] virtual uint32_t get_default_bg_channel() const = 0;

    /**
     * Gets default frontground color channel from the stdplane.
     *
     * @return The default foreground color channel.
     */
    [[nodiscard]] virtual uint32_t get_default_fg_channel() const = 0;

    /**
     * Gets default color channels from the stdplane.
     *
     * @return The combined default foreground and background channels.
     */
    [[nodiscard]] virtual uint64_t get_default_channels() const = 0;

    /**
     * Draws all actions on the screen.
     */
    virtual void render() = 0;
};

#endif
