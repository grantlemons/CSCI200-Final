#include "lib/dummies/NcHandlerDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <notcurses/notcurses.h>

ncplane *NcHandlerDummy::get_stdplane() const {
    return nullptr;
}
INcPlaneWrapper *NcHandlerDummy::get_stdplane_wrapper() const {
    return new NcPlaneWrapperDummy();
}

uint32_t NcHandlerDummy::get_default_bg_channel() const {
    return 0x0;
}
uint32_t NcHandlerDummy::get_default_fg_channel() const {
    return 0x0;
}
uint64_t NcHandlerDummy::get_default_channels() const {
    return 0x0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

uint32_t NcHandlerDummy::get_nblock(ncinput *ni) const {
    return 'a';
}
uint32_t NcHandlerDummy::get_blocking(ncinput *ni) const {
    return 'a';
}

#pragma GCC diagnostic pop

void NcHandlerDummy::render() {}
