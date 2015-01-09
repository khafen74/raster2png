#ifndef CLASSIFYRENDERER_H
#define CLASSIFYRENDERER_H

#include "renderer.h"

class ClassifyRenderer : public Renderer
{
public:
    ClassifyRenderer(const char *rasterPath, ColorRamp ramp, int nTransparency);
};

#endif // CLASSIFYRENDERER_H
