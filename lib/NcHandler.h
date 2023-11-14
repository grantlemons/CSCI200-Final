#ifndef NC_HANDLER
#define NC_HANDLER

#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"
#include "wrappers/NcPlaneWrapper.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcHandler
 * RAII Handler for a notcurses instance.
 */
class NcHandler : virtual public INcHandler {
private:
    /** The underlying notcurses instance. */
    notcurses *_nc;

public:
    /** Default red color channel value */
    static uint32_t const RED_CHANNEL;

    /** Default blue color channel value */
    static uint32_t const BLUE_CHANNEL;

    /** Default white color channel value */
    static uint32_t const WHITE_CHANNEL;

    /** Default grey color channel value */
    static uint32_t const GREY_CHANNEL;

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
    ~NcHandler() override;

    NcHandler(NcHandler &other) = delete;
    void operator=(NcHandler const &) = delete;

    [[nodiscard]] ncplane *get_stdplane() const override final;
    [[nodiscard]] INcPlaneWrapper *get_stdplane_wrapper() const override final;

    [[nodiscard]] uint32_t get_default_bg_channel() const override final;
    [[nodiscard]] uint32_t get_default_fg_channel() const override final;
    [[nodiscard]] uint64_t get_default_channels() const override final;

    /**
     * Utilitiy function to combine a foreground and background channel.
     *
     * @return The combined channels.
     */
    static uint64_t combineChannels(uint32_t const BG_CHANNEL,
                                    uint32_t const FG_CHANNEL);
    void render() override final;
};

#endif
