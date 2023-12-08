/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef DUMMY_BOARD_FACTORY
#define DUMMY_BOARD_FACTORY

#include "lib/board/LeafBoard.h"
#include "lib/board/PrimaryBoard.h"
#include "lib/factories/AbstractBoardFactory.h"
#include "lib/interfaces/IGraphicalArea.h"
#include "lib/interfaces/INcHandler.h"
#include "lib/interfaces/INcPlaneWrapper.h"

#include <memory>

/**
 * @class DummyBoardFactory
 * Factory pattern for initializing Dummy Boards.
 */
class DummyBoardFactory : virtual public AbstractBoardFactory {
private:
    std::unique_ptr<INcHandler> _ncHandler;
    INcPlaneWrapper *_primaryPlane;
    std::unique_ptr<IGraphicalBoard> _graphicalBoard;
    PrimaryBoard _primaryBoard;

public:
    /**
     * Default constructor for factory.
     */
    DummyBoardFactory();

    INcHandler *getNcHandler() override final;
    PrimaryBoard *getPrimaryBoard() override final;
    IGraphicalArea *getPrimaryGraphicalBoard() override final;
    LeafBoard *getLeafBoard(const int INDEX) override final;
    IGraphicalArea *getLeafGraphicalBoard(const int INDEX) override final;
};

#endif // !DUMMY_BOARD_FACTORY
