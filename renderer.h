#ifndef RENDERER_H
#define RENDERER_H

#include "gdal_priv.h"
#include <QtGui>

enum ColorRamp{CR_BlackWhite, CR_DEM, CR_DoD, CR_Slope};

class Renderer
{
public:
    Renderer(const char *rasterPath,
             ColorRamp ramp = CR_BlackWhite,
             int nTransparency = 255);

    int rasterToPNG(const char *pngPath,
                    int nQuality,
                    int nLength);
    int setColorTable(ColorRamp rampStyle,
                      int nTransparency);

private:
    const char *rasterPath;
    QString tempRasterPath;
    GDALDataset *pRaster, *pTempRaster;
    GDALDriver *pDriverPNG, *pDriverTiff;
    GDALColorTable colorTable;
    int nRows, nCols;
    double min, max, mean, stdev, noData, noData2;

    virtual void createByteRaster() = 0;

    int setTempRasterPath(const char*
                          rasterPath);
    int resizeAndCompressPNG(const char *inputImage,
                             int nLength,
                             int nQuality);
};

#endif // RENDERER_H
