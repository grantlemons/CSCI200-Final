#include "Board.h"
#include "GraphicalBoard.h"
#include "NcHandler.h"
#include "LeafBoard.h"
#include "PrimaryBoard.h"
#include "Shared.h"

#include <memory>
#include <optional>
using namespace std;

int main() {
    shared_ptr<NcHandler> ncHandler(new NcHandler());

    PrimaryBoard pBoard(ncHandler);

    return EXIT_SUCCESS;
}
