#include "NcHandler.h"

#include <clocale>
#include <notcurses/notcurses.h>

NcHandler::NcHandler() {
    setlocale(LC_ALL, "");
    this->nc = notcurses_init(NULL, NULL);
}

NcHandler::~NcHandler() {
    notcurses_stop(this->nc);
}

NcHandler *NcHandler::get_instance() {
    if (_singleton == nullptr) {
        _singleton = new NcHandler();
    }

    return _singleton;
}

notcurses *NcHandler::get_nc() {
    NcHandler *sgltn = NcHandler::get_instance();

    return sgltn->nc;
}

ncplane *NcHandler::get_stdplane() {
    NcHandler *sgltn = NcHandler::get_instance();

    return notcurses_stdplane(sgltn->nc);
}

void NcHandler::render() const {
    notcurses_render(this->nc);
}
