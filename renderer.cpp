#include "renderer.h"


Renderer::Renderer(const char *inputRasterPath, ColorRamp ramp, int nTransparency)
{
    pDriverTiff = GetGDALDriverManager()->GetDriverByName("GTiff");
    pDriverPNG = GetGDALDriverManager()->GetDriverByName("PNG");

    setColorTable(ramp, nTransparency);
    setupRaster(inputRasterPath);
}

int Renderer::setTempRasterPath(const char *rasterPath)
{
    QDateTime dtCurrent = QDateTime::currentDateTime();
    QString name, dirName, tempRasterPath;
    QFileInfo fileInfo(QString::fromUtf8(rasterPath));
    dirName = fileInfo.absolutePath();
    name = fileInfo.baseName();
    name = name + "_" + dtCurrent.toString("yyyyMMddhhmmss") + ".tif";
    tempRasterPath = dirName + "/" + name;

    return 0;
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

    return 0;
}

int Renderer::setColorTable(ColorRamp rampStyle, int nTransparency)
{
    GDALColorEntry trans;
    trans.c1 = 255, trans.c2 = 255, trans.c3 = 255, trans.c4 = 0;
    switch (rampStyle)
    {
    case CR_BlackWhite:
    {
        GDALColorEntry blk, wht;
        blk.c1 = 0, blk.c2 = 0, blk.c3 = 0, blk.c4 = nTransparency;
        wht.c1 = 255, wht.c2 = 255, wht.c3 = 255, wht.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &blk, 255, &wht);
        colorTable.SetColorEntry(0, &trans);
        break;
    }
    case CR_DEM:
    {
        GDALColorEntry tan, brn, grn, wht;
        tan.c1 = 255, tan.c2 = 235, tan.c3 = 176, tan.c4 = nTransparency;
        brn.c1 = 115, brn.c2 = 77, brn.c3 = 0, brn.c4 = nTransparency;
        grn.c1 = 38, grn.c2 = 115, grn.c3 = 0, grn.c4 = nTransparency;
        wht.c1 = 255, wht.c2 = 255, wht.c3 = 255, wht.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &tan, 85, &grn);
        colorTable.CreateColorRamp(85, &grn, 170, &brn);
        colorTable.CreateColorRamp(170, &brn, 255, &wht);
        colorTable.SetColorEntry(0, &trans);
        break;
    }
    case CR_DoD:
    {
        GDALColorEntry rd, wt, bl;
        rd.c1 = 230, rd.c2 = 0, rd.c3 = 0, rd.c4 = nTransparency;
        wt.c1 = 255, wt.c2 = 255, wt.c3 = 255, wt.c4 = nTransparency;
        bl.c1 = 2, bl.c2 = 77, bl.c3 = 168, bl.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &rd, 128, &wt);
        colorTable.CreateColorRamp(128, &wt, 255, &bl);
        colorTable.SetColorEntry(0, &trans);
    }
    }

    return 0;
}

int Renderer::setupRaster(const char *inputRasterPath)
{
    rasterPath = inputRasterPath;
    pRaster = (GDALDataset*) GDALOpen(rasterPath, GA_ReadOnly);

    pRaster->GetRasterBand(1)->GetStatistics(FALSE, TRUE, &min, &max, &mean, &stdev);
    pRaster->GetGeoTransform(transform);
    rasterType = pRaster->GetRasterBand(1)->GetRasterDataType();
    nRows = pRaster->GetRasterBand(1)->GetYSize();
    nCols = pRaster->GetRasterBand(1)->GetXSize();

    return 0;
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
