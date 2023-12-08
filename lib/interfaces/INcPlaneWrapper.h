/**
 * Assignment: Final Project
 * Author: Grant Lemons
 * License: GPL3.0
 * 
 * All the work in this file is my own.
 */

#ifndef NCPLANE_WRAPPERI
#define NCPLANE_WRAPPERI

#include "lib/interfaces/IGraphicalArea.h"

/**
 * @class INcPlaneWrapper
 * Interface for NcPlaneWrapper.
 */
class INcPlaneWrapper : virtual public IGraphicalArea {
public:
    ~INcPlaneWrapper() override = default;
};

#endif
