#include "GraphicalBoardDummy.h"

#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <iostream>
#include <memory>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

GraphicalBoardDummy::GraphicalBoardDummy() {}

void GraphicalBoardDummy::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {
    std::cout << "GB_DUMMY: draw_board called" << std::endl;
}
void GraphicalBoardDummy::draw_x(const unsigned int INDEX) {
    std::cout << "GB_DUMMY: draw_x called" << std::endl;
}
void GraphicalBoardDummy::draw_o(const unsigned int INDEX) {
    std::cout << "GB_DUMMY: draw_o called" << std::endl;
}
void GraphicalBoardDummy::fill_x() {
    std::cout << "GB_DUMMY: fill_x called" << std::endl;
}
void GraphicalBoardDummy::fill_o() {
    std::cout << "GB_DUMMY: fill_o called" << std::endl;
}

std::array<NcPlaneWrapperI *, CELL_COUNT> *
GraphicalBoardDummy::get_child_planes() {
    std::cout << "GB_DUMMY: get_child_planes called" << std::endl;

    std::array<NcPlaneWrapperI *, CELL_COUNT> *planes =
        new std::array<NcPlaneWrapperI *, CELL_COUNT>{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        planes->at(i) = new NcPlaneWrapperDummy();
    }

    return planes;
}

std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
GraphicalBoardDummy::create_child_boards() const {
    std::cout << "GB_DUMMY: create_child_boards called" << std::endl;
    std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT> boards{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        boards.at(i) =
            std::unique_ptr<GraphicalBoardI>(new GraphicalBoardDummy());
    }

    return boards;
}

#pragma GCC diagnostic pop
