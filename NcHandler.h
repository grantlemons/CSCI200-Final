#ifndef NC_HANDLER
#define NC_HANDLER

#include <memory>
#include <notcurses/notcurses.h>

// singleton used for raii access to notcurses object
class NcHandler {
private:
    static NcHandler *_singleton;

    NcHandler();

public:
    notcurses *nc;

    ~NcHandler();
    NcHandler(NcHandler &other) = delete;
    void operator=(const NcHandler &) = delete;

    static NcHandler *get_instance();
    static notcurses *get_nc();
    static ncplane *get_stdplane();

    void render() const;
};

#endif
