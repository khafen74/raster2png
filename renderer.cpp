#include "renderer.h"


Renderer::Renderer(const char *rasterPath, ColorRamp ramp, int nTransparency)
{
    pDriverTiff = GetGDALDriverManager()->GetDriverByName("GTiff");
    pDriverPNG = GetGDALDriverManager()->GetDriverByName("PNG");
}

int Renderer::setColorTable(ColorRamp rampStyle, int nTransparency)
{
    switch (rampStyle)
    {
        case CR_BlackWhite:
        case CR_DEM:
        case CR_DoD:
        case CR_Slope:;

    }
}

int Renderer::rasterToPNG(const char *pngPath, int nQuality, int nLength)
{
    GDALDataset *pPngDS;
    pDriverPNG = GetGDALDriverManager()->GetDriverByName("PNG");

    pPngDS = pDriverPNG->CreateCopy(pngPath,pTempRaster,FALSE,NULL,NULL,NULL);
    //set transform here

    GDALClose(pTempRaster);
    GDALClose(pPngDS);

    //resize and compress
    resizeAndCompressPNG(pngPath, nLength, nQuality);
}

int Renderer::resizeAndCompressPNG(const char *inputImage, int nLength, int nQuality)
{
    QImage image = QImage(QString::fromUtf8(inputImage));

    //determine if height or width is greater and rescale
    if (image.height() > image.width())
    {
        image = image.scaledToHeight(nLength, Qt::SmoothTransformation);
    }
    else
    {
        image = image.scaledToWidth(nLength, Qt::SmoothTransformation);
    }

    //save and compress the image
    image.save(QString::fromUtf8(inputImage), 0, nQuality);

    return 0;
}
