#include "NcHandler.h"

#include <clocale>
#include <iostream>
#include <notcurses/notcurses.h>

NcHandler::NcHandler() {
    setlocale(LC_ALL, "");
    this->nc = notcurses_init(NULL, NULL);
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
