#ifndef NC_HANDLER_DUMMY
#define NC_HANDLER_DUMMY

#include "lib/interfaces/INcHandler.h"

#include <cstdint>
#include <notcurses/notcurses.h>

/**
 * @class NcHandlerDummy
 * Dummy class used as a substitute for INcHandler classes for testing
 * purposes.
 */
class NcHandlerDummy : virtual public INcHandler {
public:
    NcHandlerDummy() = default;

    NcHandlerDummy(NcHandlerDummy &other) = delete;
    void operator=(const NcHandlerDummy &) = delete;

    [[nodiscard]] ncplane *get_stdplane() const override final;
    [[nodiscard]] INcPlaneWrapper *get_stdplane_wrapper() const override final;

    [[nodiscard]] uint32_t get_default_bg_channel() const override final;
    [[nodiscard]] uint32_t get_default_fg_channel() const override final;
    [[nodiscard]] uint64_t get_default_channels() const override final;

    void render() override final;
};

#endif
