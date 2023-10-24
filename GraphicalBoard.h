#ifndef G_BOARD
#define G_BOARD

#include "NcHandler.h"
#include <cstdint>
#include <memory>
#include <notcurses/notcurses.h>

class GraphicalBoard {
private:
    ncplane *_plane;
    std::shared_ptr<NcHandler> _ncHandler;

    unsigned int _y, _x;
    unsigned int _rows, _cols;
    const char **_symbols;
    uint64_t _cell_channels;

    int draw_board_yx(const int Y, const int X,
                      const unsigned int ROWS_PER_BCELL,
                      const unsigned int COLS_PER_BCELL);
    int draw_x_yx(const int Y, const int X);
    int draw_o_yx(const int Y, const int X);

public:
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, const int Y,
                   const int X, const unsigned int ROWS,
                   const unsigned int COLS, const char **const SYMBOLS);
    GraphicalBoard(std::shared_ptr<NcHandler> ncHandler, ncplane_options nopts,
                   const char **const SYMBOLS);
    ~GraphicalBoard() = default;
    void draw_board();
    void draw_x(const unsigned int INDEX);
    void draw_o(const unsigned int INDEX);
};

#endif // !G_BOARD
