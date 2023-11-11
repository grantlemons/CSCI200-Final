#ifndef NC_HANDLER_DUMMY
#define NC_HANDLER_DUMMY

#include "lib/interfaces/NcHandlerI.h"

#include <cstdint>
#include <notcurses/notcurses.h>

class NcHandlerDummy : public NcHandlerI {
public:
    uint32_t get_default_bg_channel() const override final;
    uint32_t get_default_fg_channel() const override final;
    uint64_t get_default_channels() const override final;
    notcurses *get_nc() const override final;
    ncplane *get_stdplane() const override final;
    void render() override final;
};

#endif
