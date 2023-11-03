#ifndef NC_HANDLER
#define NC_HANDLER

#include <cstdint>
#include <notcurses/notcurses.h>

// raii access to notcurses object
class NcHandler {
public:
    notcurses *nc;

    static const uint32_t RED_CHANNEL;
    static const uint32_t BLUE_CHANNEL;
    static const uint32_t WHITE_CHANNEL;
    static const uint32_t GREY_CHANNEL;

    NcHandler();
    ~NcHandler();

    NcHandler(NcHandler &other) = delete;
    void operator=(const NcHandler &) = delete;

    uint32_t get_default_bg_channel() const;
    uint32_t get_default_fg_channel() const;
    uint64_t get_default_channels() const;
    static uint64_t combine_channels(const uint32_t BG_CHANNEL,
                                     const uint32_t FG_CHANNEL);
    notcurses *get_nc() const;
    ncplane *get_stdplane() const;
    void render();
};

#endif
