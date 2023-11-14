#include "lib/factories/DummyBoardFactory.h"

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/dummies/GraphicalBoardDummy.h"
#include "lib/dummies/NcHandlerDummy.h"
#include "lib/dummies/NcPlaneWrapperDummy.h"
#include "lib/interfaces/GraphicalAreaI.h"
#include "lib/interfaces/NcHandlerI.h"
#include "lib/interfaces/NcPlaneWrapperI.h"

#include <memory>

DummyBoardFactory::DummyBoardFactory()
    : _ncHandler{std::unique_ptr<NcHandlerI>{new NcHandlerDummy{}}},
      _primaryPlane{new NcPlaneWrapperDummy{}},
      _graphicalBoard{std::unique_ptr<GraphicalBoardI>{
          new GraphicalBoardDummy{_primaryPlane}}},
      _primaryBoard{_ncHandler.get(), std::move(_graphicalBoard)} {}

NcHandlerI *DummyBoardFactory::getNcHandler() {
    return _ncHandler.get();
}
PrimaryBoard *DummyBoardFactory::getPrimaryBoard() {
    return &_primaryBoard;
}
GraphicalAreaI *DummyBoardFactory::getPrimaryGraphicalBoard() {
    return _primaryBoard.getGraphicalBoard();
}
LeafBoard *DummyBoardFactory::getLeafBoard(const int INDEX) {
    return _primaryBoard.getLeafBoard(INDEX);
}
GraphicalAreaI *DummyBoardFactory::getLeafGraphicalBoard(const int INDEX) {
    return getLeafBoard(INDEX)->getGraphicalBoard();
}
