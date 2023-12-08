/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/NcHandler.h"

#include "gsl/assert"
#include "interfaces/INcPlaneWrapper.h"
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

const notcurses_options NOPTS = {nullptr, NCLOGLEVEL_SILENT,        0, 0, 0,
                                 0,       NCOPTION_SUPPRESS_BANNERS};

NcHandler::NcHandler() : _nc{notcurses_init(&NOPTS, nullptr)} {
    setlocale(LC_ALL, "");

    Ensures(_nc != nullptr);
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

uint32_t NcHandler::get_nblock(ncinput *ni) const {
    return notcurses_get_nblock(_nc, ni);
}
uint32_t NcHandler::get_blocking(ncinput *ni) const {
    return notcurses_get_blocking(_nc, ni);
}

uint64_t NcHandler::combineChannels(const uint32_t BG_CHANNEL,
                                    const uint32_t FG_CHANNEL) {
    const unsigned long long int CHANNEL_SIZE_BITS = 32;
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
