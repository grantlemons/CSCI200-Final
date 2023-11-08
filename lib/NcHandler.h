#ifndef NC_HANDLER
#define NC_HANDLER

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcHandler
 * RAII Handler for a notcurses instance.
 */
class NcHandler {
public:
    /** The underlying notcurses instance. */
    notcurses *nc;

    /** Default red color channel value */
    static const uint32_t RED_CHANNEL;

    /** Default blue color channel value */
    static const uint32_t BLUE_CHANNEL;

    /** Default white color channel value */
    static const uint32_t WHITE_CHANNEL;

    /** Default grey color channel value */
    static const uint32_t GREY_CHANNEL;

    /**
     * Constructor used to instantiate a notcurses instance.
     *
     * Also sets locale.
     *
     * @see notcurses_init()
     */
    NcHandler();

    /**
     * Destructor used to stop notcurses instance.
     *
     * @see notcurses_stop()
     */
    ~NcHandler();

    NcHandler(NcHandler &other) = delete;
    void operator=(const NcHandler &) = delete;

    /**
     * Gets default background color channel from the stdplane.
     *
     * @return The default background color channel.
     */
    uint32_t get_default_bg_channel() const;

    /**
     * Gets default frontground color channel from the stdplane.
     *
     * @return The default foreground color channel.
     */
    uint32_t get_default_fg_channel() const;

    /**
     * Gets default color channels from the stdplane.
     *
     * @return The combined default foreground and background channels.
     */
    uint64_t get_default_channels() const;

    /**
     * Utilitiy function to combine a foreground and background channel.
     *
     * @return The combined channels.
     */
    static uint64_t combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL);

    /**
     * Getter for notcurses instance.
     *
     * @return The underlying notcurses instance.
     */
    notcurses *get_nc() const;

    /**
     * Getter for notcurses stdplane.
     *
     * @return The stdplane for the notcurses instance.
     */
    ncplane *get_stdplane() const;

    /**
     * Draws all actions on the screen.
     */
    void render();
};

#endif
