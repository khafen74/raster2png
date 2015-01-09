#ifndef STRETCHRENDERERSTDEV_H
#define STRETCHRENDERERSTDEV_H

#include "renderer.h"

class StretchRendererStDev : public Renderer
{
public:
    StretchRendererStDev(const char *rasterPath, ColorRamp ramp, int nTransparency);

private:
    double stdStretch;
};

#endif // STRETCHRENDERERSTDEV_H
