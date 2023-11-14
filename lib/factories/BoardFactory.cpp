#include "lib/factories/BoardFactory.h"

#include "lib/NcHandler.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <memory>

BoardFactory::BoardFactory()
    : _ncHandler{std::unique_ptr<NcHandlerI>{new NcHandler{}}},
      _primaryBoard{_ncHandler.get()} {}

NcHandlerI *BoardFactory::getNcHandler() {
    return _ncHandler.get();
}
PrimaryBoard *BoardFactory::getPrimaryBoard() {
    return &_primaryBoard;
}
GraphicalAreaI *BoardFactory::getPrimaryGraphicalBoard() {
    return _primaryBoard.getGraphicalBoard();
}
LeafBoard *BoardFactory::getLeafBoard(const int INDEX) {
    return _primaryBoard.getLeafBoard(INDEX);
}
GraphicalAreaI *BoardFactory::getLeafGraphicalBoard(const int INDEX) {
    return getLeafBoard(INDEX)->getGraphicalBoard();
}
