#include "doctest.h"
#include "lib/NcHandler.h"
#include "lib/board/LeafBoard.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <memory>

LeafBoard create_l_board();
LeafBoard create_l_board() {
    std::shared_ptr<NcHandlerI> handler{new NcHandler()};
    std::unique_ptr<NcPlaneWrapperI> planeWrapper{new NcPlaneWrapperDummy()};

    return LeafBoard{handler, std::move(planeWrapper)};
}

TEST_SUITE("Leaf Board Tests") {
    TEST_CASE("Test Cells Init") {}
}
