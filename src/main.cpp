#include "lib/NcHandler.h"
#include "lib/Shared.h"
#include "lib/board/Board.h"
#include "lib/board/GraphicalBoard.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"

#include <memory>
#include <optional>

int main() {
    std::shared_ptr<NcHandler> ncHandler(new NcHandler());

    PrimaryBoard pBoard(ncHandler);

    while (1);

    return EXIT_SUCCESS;
}
