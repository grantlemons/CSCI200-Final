#include "lib/NcHandler.h"

#include "interfaces/NcPlaneWrapperI.h"
#include "wrappers/NcPlaneWrapper.h"

#include <clocale>
#include <cstdint>
#include <notcurses/notcurses.h>

const uint32_t NcHandler::RED_CHANNEL = NCCHANNEL_INITIALIZER(0xc3, 0x40, 0x43);
const uint32_t NcHandler::BLUE_CHANNEL =
    NCCHANNEL_INITIALIZER(0x7e, 0x9c, 0xd8);
const uint32_t NcHandler::WHITE_CHANNEL =
    NCCHANNEL_INITIALIZER(0xff, 0xff, 0xff);
const uint32_t NcHandler::GREY_CHANNEL =
    NCCHANNEL_INITIALIZER(0x77, 0x77, 0x77);

const notcurses_options opts = {nullptr,
                                NCLOGLEVEL_SILENT,
                                0,
                                0,
                                0,
                                0,
                                NCOPTION_SUPPRESS_BANNERS +
                                    NCOPTION_DRAIN_INPUT};

NcHandler::NcHandler() {
    setlocale(LC_ALL, "");
    nc = notcurses_init(&opts, nullptr);
}

NcHandler::~NcHandler() {
    notcurses_stop(nc);
    nc = nullptr;
}

uint32_t NcHandler::get_default_bg_channel() const {
    return ncplane_bchannel(notcurses_stdplane(nc));
}
uint32_t NcHandler::get_default_fg_channel() const {
    return ncplane_fchannel(notcurses_stdplane(nc));
}
uint64_t NcHandler::get_default_channels() const {
    return ncplane_channels(notcurses_stdplane(nc));
}

uint64_t NcHandler::combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL) {

    return (static_cast<uint64_t>(FG_CHANNEL) << 32ull) + BG_CHANNEL;
}

ncplane *NcHandler::get_stdplane() const {
    return notcurses_stdplane(nc);
}

NcPlaneWrapperI *NcHandler::get_stdplane_wrapper() const {
    return new NcPlaneWrapper(notcurses_stdplane(nc), true);
}

void NcHandler::render() {
    notcurses_render(nc);
}
