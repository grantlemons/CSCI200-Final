#include "LeafGraphicalBoardDummy.h"

#include "lib/dummies/AGraphicalBoardDummy.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

LeafGraphicalBoardDummy::LeafGraphicalBoardDummy(
    std::shared_ptr<INcPlaneWrapper> plane)
    : AGraphicalBoardDummy(std::move(plane)) {
    set_children(create_children());
}

std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT>
LeafGraphicalBoardDummy::create_children() {
    std::array<std::unique_ptr<IGraphicalArea>, CELL_COUNT> children{};

    for (unsigned int i = 0; i < CELL_COUNT; i++) {
        children.at(i) = std::make_unique<NcPlaneWrapperDummy>();
    }

    return children;
}
