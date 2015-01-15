#ifndef RENDERER_GCDPTDENS_H
#define RENDERER_GCDPTDENS_H

#include "renderer_classified.h"

class Renderer_GCDPtDens : public Renderer_Classified
{
public:
    Renderer_GCDPtDens(const char *rasterPath,
                       int classCount,
                       ColorRamp ramp,
                       int nTransparency,
                       bool centerOnZero,
                       bool displayZeroNoData);
};

#endif // RENDERER_GCDPTDENS_H
