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
     */
    NcHandler();

    /**
     * Destructor used to stop notcurses instance.
     */
    ~NcHandler() override;

    NcHandler(NcHandler &other) = delete;
    void operator=(const NcHandler &) = delete;

    [[nodiscard]] ncplane *get_stdplane() const override final;
    [[nodiscard]] INcPlaneWrapper *get_stdplane_wrapper() const override final;

    [[nodiscard]] uint32_t get_default_bg_channel() const override final;
    [[nodiscard]] uint32_t get_default_fg_channel() const override final;
    [[nodiscard]] uint64_t get_default_channels() const override final;

    uint32_t get_nblock(ncinput *ni) const override final;
    uint32_t get_blocking(ncinput *ni) const override final;

    /**
     * Utilitiy function to combine a foreground and background channel.
     *
     * @return The combined channels.
     */
    static uint64_t combineChannels(const uint32_t BG_CHANNEL,
                                    const uint32_t FG_CHANNEL);
    void render() override final;
};

#endif
