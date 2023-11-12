#ifndef NC_HANDLER_DUMMY
#define NC_HANDLER_DUMMY

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <notcurses/notcurses.h>

class NcHandlerDummy : public NcHandlerI {
public:
    NcHandlerDummy(NcHandlerDummy &other) = delete;
    void operator=(const NcHandlerDummy &) = delete;

    ncplane *get_stdplane() const override final;
    NcPlaneWrapperI *get_stdplane_wrapper() const override final;

    uint32_t get_default_bg_channel() const override final;
    uint32_t get_default_fg_channel() const override final;
    uint64_t get_default_channels() const override final;

    void render() override final;
};

#endif
