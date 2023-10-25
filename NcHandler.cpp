#include "NcHandler.h"

#include <clocale>
#include <notcurses/notcurses.h>

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

notcurses *NcHandler::get_nc() {
    return this->nc;
}

ncplane *NcHandler::get_stdplane() {
    return notcurses_stdplane(this->nc);
}

void NcHandler::render() {
    notcurses_render(this->nc);
}
