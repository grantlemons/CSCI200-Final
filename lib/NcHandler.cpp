#include "lib/NcHandler.h"

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

const notcurses_options opts = {NULL,
                                NCLOGLEVEL_SILENT,
                                0,
                                0,
                                0,
                                0,
                                NCOPTION_SUPPRESS_BANNERS +
                                    NCOPTION_DRAIN_INPUT};

NcHandler::NcHandler() {
    setlocale(LC_ALL, "");
    this->nc = notcurses_init(&opts, NULL);
}

NcHandler::~NcHandler() {
    notcurses_stop(this->nc);
    this->nc = nullptr;
}

uint32_t NcHandler::get_default_bg_channel() {
    return ncplane_bchannel(this->get_stdplane());
}
uint32_t NcHandler::get_default_fg_channel() {
    return ncplane_fchannel(this->get_stdplane());
}

uint64_t NcHandler::combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL) {

    return ((uint64_t)FG_CHANNEL << 32ull) + BG_CHANNEL;
}

notcurses *NcHandler::get_nc() {
    return this->nc;
}

ncplane *NcHandler::get_stdplane() {
    return notcurses_stdplane(this->nc);
}

void NcHandler::render() {
    notcurses_render(this->nc);
}
