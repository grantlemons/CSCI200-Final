#include "GraphicalBoardDummy.h"

#include "lib/interfaces/NcPlaneWrapperI.h"

#include <iostream>

void GraphicalBoardDummy::draw_board(
    const std::array<const char *, SYMBOL_COUNT> SYMBOLS,
    const uint64_t CELL_CHANNELS) {
    std::cout << "GB_DUMMY: draw_board called" << std::endl;
    std::cout << "GB_DUMMY: Symbols: " << &SYMBOLS;
    std::cout << " Channels: " << CELL_CHANNELS << std::endl;
}
void GraphicalBoardDummy::draw_x(const unsigned int INDEX) {
    std::cout << "GB_DUMMY: draw_x called" << std::endl;
    std::cout << "GB_DUMMY: Index: " << INDEX << std::endl;
}
void GraphicalBoardDummy::draw_o(const unsigned int INDEX) {
    std::cout << "GB_DUMMY: draw_o called" << std::endl;
    std::cout << "GB_DUMMY: Index: " << INDEX << std::endl;
}
void GraphicalBoardDummy::fill_x() {
    std::cout << "GB_DUMMY: fill_x called" << std::endl;
}
void GraphicalBoardDummy::fill_o() {
    std::cout << "GB_DUMMY: fill_o called" << std::endl;
}
std::array<NcPlaneWrapperI *, CELL_COUNT> *
GraphicalBoardDummy::get_child_planes() {}
std::array<std::unique_ptr<GraphicalBoardI>, CELL_COUNT>
GraphicalBoardDummy::create_child_boards() const {}
