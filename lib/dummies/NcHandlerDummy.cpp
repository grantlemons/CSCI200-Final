#include "lib/dummies/NcHandlerDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"

#include <notcurses/notcurses.h>

NcHandlerDummy::NcHandlerDummy() {}

ncplane *NcHandlerDummy::get_stdplane() const {
    return nullptr;
}
NcPlaneWrapperI *NcHandlerDummy::get_stdplane_wrapper() const {
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

void NcHandlerDummy::render() {}
