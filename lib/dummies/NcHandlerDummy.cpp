#include "lib/dummies/NcHandlerDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"

#include <iostream>
#include <notcurses/notcurses.h>

NcHandlerDummy::NcHandlerDummy() {}

ncplane *NcHandlerDummy::get_stdplane() const {
    std::cout << "NC_DUMMY: get_stdplane called" << std::endl;
    return nullptr;
}
NcPlaneWrapperI *NcHandlerDummy::get_stdplane_wrapper() const {
    std::cout << "NC_DUMMY: get_stdplane_wrapper called" << std::endl;
    return new NcPlaneWrapperDummy();
}

uint32_t NcHandlerDummy::get_default_bg_channel() const {
    std::cout << "NC_DUMMY: get_default_bg_channel called" << std::endl;
    return 0x0;
}
uint32_t NcHandlerDummy::get_default_fg_channel() const {
    std::cout << "NC_DUMMY: get_default_fg_channel called" << std::endl;
    return 0x0;
}
uint64_t NcHandlerDummy::get_default_channels() const {
    std::cout << "NC_DUMMY: get_default_channels called" << std::endl;
    return 0x0;
}

void NcHandlerDummy::render() {
    std::cout << "NC_DUMMY: render called" << std::endl;
}
