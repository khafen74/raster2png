#ifndef RASTER2PNG_H
#define RASTER2PNG_H

#include <iostream>
#include "renderer_bytedata.h"
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"

enum RenderStyle
{
    RS_Classified
    ,RS_Stretched
    ,RS_Brightness
};

class Raster2PNG
{
public:
    Raster2PNG();
    Raster2PNG(int argc, char * argv[]);

    int init(int argc, char * argv[]);
    int run();

    int CreateStretchedPNG();
    int CreateClassifiedPNG();
    int CreateBrightnessPNG();
    ColorRamp GetColorRampFromString(const char * ramp);
    RenderStyle GetRenderStyleFromString(const char * style);
    void PrintHelp();

private:
    const char * mInputRaster, * mOutputPng;
    int m_nTransparency, m_nQuality, m_nLongAxisPixels, m_nClasses;
    double mStdDev;
    bool m_bZeroCenter, m_bZeroNoData, m_bLegend;
    ColorRamp mColorRamp;
    RenderStyle mStyle;
};

#endif // RASTER2PNG_H
