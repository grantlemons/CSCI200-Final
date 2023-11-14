#include "lib/NcHandler.h"

#include "interfaces/INcPlaneWrapper.h"
#include "wrappers/NcPlaneWrapper.h"

#include <clocale>
#include <cstdint>
#include <notcurses/notcurses.h>

uint32_t const NcHandler::RED_CHANNEL = NCCHANNEL_INITIALIZER(0xc3, 0x40, 0x43);
uint32_t const NcHandler::BLUE_CHANNEL =
    NCCHANNEL_INITIALIZER(0x7e, 0x9c, 0xd8);
uint32_t const NcHandler::WHITE_CHANNEL =
    NCCHANNEL_INITIALIZER(0xff, 0xff, 0xff);
uint32_t const NcHandler::GREY_CHANNEL =
    NCCHANNEL_INITIALIZER(0x77, 0x77, 0x77);

notcurses_options const NOPTS = {nullptr,
                                 NCLOGLEVEL_SILENT,
                                 0,
                                 0,
                                 0,
                                 0,
                                 NCOPTION_SUPPRESS_BANNERS +
                                     NCOPTION_DRAIN_INPUT};

NcHandler::NcHandler() : _nc{notcurses_init(&NOPTS, nullptr)} {
    setlocale(LC_ALL, "");
}

NcHandler::~NcHandler() {
    notcurses_stop(_nc);
    _nc = nullptr;
}

uint32_t NcHandler::get_default_bg_channel() const {
    return ncplane_bchannel(notcurses_stdplane(_nc));
}
uint32_t NcHandler::get_default_fg_channel() const {
    return ncplane_fchannel(notcurses_stdplane(_nc));
}
uint64_t NcHandler::get_default_channels() const {
    return ncplane_channels(notcurses_stdplane(_nc));
}

uint64_t NcHandler::combineChannels(uint32_t const BG_CHANNEL,
                                    uint32_t const FG_CHANNEL) {
    unsigned long long int const CHANNEL_SIZE_BITS = 32;
    return (static_cast<uint64_t>(FG_CHANNEL) << CHANNEL_SIZE_BITS) +
           BG_CHANNEL;
}

ncplane *NcHandler::get_stdplane() const {
    return notcurses_stdplane(_nc);
}

INcPlaneWrapper *NcHandler::get_stdplane_wrapper() const {
    return new NcPlaneWrapper(notcurses_stdplane(_nc), true);
}

void NcHandler::render() {
    notcurses_render(_nc);
}
