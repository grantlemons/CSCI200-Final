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
