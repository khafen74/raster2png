#include "renderer_gcdptdens.h"

Renderer_GCDPtDens::Renderer_GCDPtDens(const char *rasterPath,
                                       int classCount,
                                       ColorRamp ramp,
                                       int nTransparency,
                                       bool centerOnZero,
                                       bool displayZeroNoData):Renderer_Classified(rasterPath,classCount, ramp, nTransparency, centerOnZero, displayZeroNoData)
{
}
