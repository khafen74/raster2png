#ifndef RENDERER_H
#define RENDERER_H

#include "gdal_priv.h"
#include <QtGui>

enum ColorRamp{CR_BlackWhite, CR_DEM, CR_DoD, CR_GrainSize, CR_GreenBlue, CR_Precipitation, CR_Slope, CR_SlopeGCD};

class Renderer
{
public:
    Renderer(const char *inputRasterPath,
             ColorRamp ramp = CR_BlackWhite,
             int nTransparency = 255);

    int rasterToPNG(const char *pngPath,
                    int nQuality,
                    int nLength);
    int setColorTable(ColorRamp rampStyle,
                      int nTransparency);
    int setupRaster(const char *inputRasterPath);

private:
    const char *rasterPath;
    QString tempRasterPath;
    GDALDataset *pRaster, *pTempRaster;
    GDALDriver *pDriverPNG, *pDriverTiff;
    GDALColorTable colorTable;
    GDALDataType rasterType;
    int nRows, nCols;
    double min, max, mean, stdev, noData, noData2;
    double transform[6];
    bool zeroNoData;

    virtual void createByteRaster() = 0;

    int setTempRasterPath(const char*
                          rasterPath);
    int resizeAndCompressPNG(const char *inputImage,
                             int nLength,
                             int nQuality);
};

#endif // RENDERER_H
