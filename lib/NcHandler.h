#ifndef NC_HANDLER
#define NC_HANDLER

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcHandler
 * RAII Handler for a notcurses instance.
 */
class NcHandler : public NcHandlerI {
private:
    /** The underlying notcurses instance. */
    notcurses *nc;

public:
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

    uint32_t get_default_bg_channel() const;
    uint32_t get_default_fg_channel() const;
    uint64_t get_default_channels() const;

    /**
     * Utilitiy function to combine a foreground and background channel.
     *
     * @return The combined channels.
     */
    static uint64_t combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL);
    ncplane *get_stdplane() const;
    void render();
};

#endif
