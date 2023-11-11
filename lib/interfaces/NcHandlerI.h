#ifndef NC_HANDLERI
#define NC_HANDLERI

#include <cstdint>
#include <notcurses/notcurses.h>

class NcHandlerI {
public:
    /*
     * Gets default background color channel from the stdplane.
     *
     * @return The default background color channel.
     */
    virtual uint32_t get_default_bg_channel() const = 0;

    /**
     * Gets default frontground color channel from the stdplane.
     *
     * @return The default foreground color channel.
     */
    virtual uint32_t get_default_fg_channel() const = 0;

    /**
     * Gets default color channels from the stdplane.
     *
     * @return The combined default foreground and background channels.
     */
    virtual uint64_t get_default_channels() const = 0;

    /**
     * Getter for notcurses stdplane.
     *
     * @return The stdplane for the notcurses instance.
     */
    virtual ncplane *get_stdplane() const = 0;

    /**
     * Draws all actions on the screen.
     */
    virtual void render() = 0;
};

#endif
