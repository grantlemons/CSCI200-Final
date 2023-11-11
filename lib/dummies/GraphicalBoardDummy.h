#ifndef G_BOARD_DUMMY
#define G_BOARD_DUMMY

#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/interfaces/GraphicalBoardI.h"

#include <array>
#include <cstdint>
#include <memory>

class GraphicalBoardDummy : public GraphicalBoardI {
public:
    void draw_board(const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
                    const uint64_t CELL_CHANNELS) override final;
    void draw_x(const unsigned int INDEX) override final;
    void draw_o(const unsigned int INDEX) override final;
    void fill_x() override final;
    void fill_o() override final;
    std::array<ncplane *, CELL_COUNT> get_child_planes() const override final;
    std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
    create_child_boards() const override final;
};

#endif
