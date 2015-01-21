#ifndef RENDERER_H
#define RENDERER_H

#include "gdal_priv.h"
#include <QtGui>

enum ColorRamp{CR_BlackWhite, CR_DEM, CR_DoD, CR_GrainSize, CR_GreenBlue, CR_PartialSpectrum, CR_Precipitation, CR_Slope, CR_SlopeGCD};

class Renderer
{
public:
    Renderer(const char *inputRasterPath,
             ColorRamp ramp = CR_BlackWhite,
             int nTransparency = 255,
             bool zeroNoData = FALSE);
    ~Renderer();

    int rasterToPNG(const char *pngPath,
                    int nQuality,
                    int nLength);
    int setRendererColorTable(ColorRamp rampStyle,
                      int nTransparency);
    void setZeroNoData(bool bValue);

protected:
    const char *rasterPath;
    float *oldRow;
    unsigned char *newRow;
    QString tempRasterPath;
    GDALDataset *pRaster, *pTempRaster, *pPngDS;
    GDALDriver *pDriverPNG, *pDriverTiff;
    GDALColorTable *colorTable;
    GDALDataType rasterType;
    int nRows, nCols;
    double min, max, mean, stdev, noData, noData2;
    double adjMin, adjMax, adjMean, range;
    double transform[6];
    bool zeroNoData, zeroCenter;

    void cleanUp();
    virtual void createByteRaster() = 0;
    int resizeAndCompressPNG(const char *inputImage,
                             int nLength,
                             int nQuality);
    int setTempRasterPath(const char*
                          rasterPath);
    void setup();
    int setupRaster(const char *inputRasterPath);
};

#endif // RENDERER_H
