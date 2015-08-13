#ifndef RASTER2PNG_H
#define RASTER2PNG_H

#include "renderer_bytedata.h"
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"

class raster2png
{
public:
    raster2png();
    raster2png(int argc, char * argv[]);

    int init(int argc, char * argv[]);
    int run();

    int CreateStretchedPNG();
    int CreateClassifiedPNG();
    int CreateBrightnessPNG();

private:
    const char * mInputRaster, * mOutputPng;
    int m_nTransparency, m_nQuality, m_nLongAxisPixels, m_nClasses;
    double mStdDev;
    bool m_bZeroCenter, m_bZeroNoData, m_bLegend;
};

#endif // RASTER2PNG_H
