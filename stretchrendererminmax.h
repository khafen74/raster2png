#ifndef STRETCHRENDERERMINMAX_H
#define STRETCHRENDERERMINMAX_H

#include "renderer.h"

class StretchRendererMinMax : public Renderer
{
public:
    StretchRendererMinMax(const char *rasterPath, ColorRamp ramp, int nTransparency);
};

#endif // STRETCHRENDERERMINMAX_H
