/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#include "lib/factories/BoardFactory.h"

#include "lib/NcHandler.h"
#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

BoardFactory::BoardFactory()
    : _ncHandler{std::unique_ptr<INcHandler>{new NcHandler{}}},
      _primaryBoard{_ncHandler.get()} {}

INcHandler *BoardFactory::getNcHandler() {
    return _ncHandler.get();
}
PrimaryBoard *BoardFactory::getPrimaryBoard() {
    return &_primaryBoard;
}
IGraphicalArea *BoardFactory::getPrimaryGraphicalBoard() {
    return _primaryBoard.getGraphicalBoard();
}
LeafBoard *BoardFactory::getLeafBoard(const int INDEX) {
    return _primaryBoard.getLeafBoard(INDEX);
}
IGraphicalArea *BoardFactory::getLeafGraphicalBoard(const int INDEX) {
    return getLeafBoard(INDEX)->getGraphicalBoard();
}
