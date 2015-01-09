#ifndef RENDERER_H
#define RENDERER_H

#include "gdal_priv.h"
#include <QtGui>

enum ColorRamp{CR_BlackWhite, CR_DEM, CR_DoD, CR_Slope};

class Renderer
{
public:
    Renderer(const char *rasterPath, ColorRamp ramp, int nTransparency);

private:
    const char *rasterPath;
    GDALDataset *pRaster, *pTempRaster;
    GDALDriver *pDriverPNG, *pDriverTiff;
    GDALColorTable colorTable;
    double min, max, mean, stdev;

    virtual void createByteRaster() = 0;

    int setColorTable(ColorRamp rampStyle, int nTransparency);
    int rasterToPNG(const char *pngPath, int nQuality, int nLength);
    int resizeAndCompressPNG(const char *inputImage, int nLength, int nQuality);
};

#endif // RENDERER_H
