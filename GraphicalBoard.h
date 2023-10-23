#ifndef G_BOARD
#define G_BOARD

#include <notcurses/notcurses.h>
#include <unistd.h>

class GraphicalBoard {
private:
    ncplane *_plane;
    unsigned int _y, _x;
    unsigned int _rows, _cols;
    const char **_symbols;

    int draw_board_yx(const int y, const int x,
                      const unsigned int ROWS_PER_BCELL,
                      const unsigned int COLS_PER_BCELL);
    int draw_x_yx(const int y, const int x, const char **SYMBOLS);
    int draw_o_yx(const int y, const int x, const char **SYMBOLS);

public:
    GraphicalBoard(notcurses *nc, const unsigned int Y, const unsigned int X,
                   const unsigned int ROWS, const unsigned int COLS,
                   const char **SYMBOLS);
    void draw_board();
    void draw_x(const unsigned int INDEX);
    void draw_o(const unsigned int INDEX);
};

#endif // !G_BOARD
