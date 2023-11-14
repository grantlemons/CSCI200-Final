#ifndef NC_HANDLER
#define NC_HANDLER

#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"
#include "wrappers/NcPlaneWrapper.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcHandler
 * RAII Handler for a notcurses instance.
 */
class NcHandler : virtual public NcHandlerI {
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

    ncplane *get_stdplane() const override final;
    NcPlaneWrapperI *get_stdplane_wrapper() const override final;

    uint32_t get_default_bg_channel() const override final;
    uint32_t get_default_fg_channel() const override final;
    uint64_t get_default_channels() const override final;

    /**
     * Utilitiy function to combine a foreground and background channel.
     *
     * @return The combined channels.
     */
    static uint64_t combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL);
    void render() override final;
};

#endif
