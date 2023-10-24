#ifndef NC_HANDLER
#define NC_HANDLER

#include <notcurses/notcurses.h>

// raii access to notcurses object
class NcHandler {
public:
    notcurses *nc;

    NcHandler();
    ~NcHandler();

    NcHandler(NcHandler &other) = delete;
    void operator=(const NcHandler &) = delete;

    notcurses *get_nc();
    ncplane *get_stdplane();
    void render();
};

#endif
