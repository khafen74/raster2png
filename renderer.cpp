#include "renderer.h"


Renderer::Renderer(const char *inputRasterPath, ColorRamp ramp, int nTransparency)
{
    pDriverTiff = GetGDALDriverManager()->GetDriverByName("GTiff");
    pDriverPNG = GetGDALDriverManager()->GetDriverByName("PNG");

    setColorTable(ramp, nTransparency);
    setupRaster(inputRasterPath);
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
    case CR_GreenBlue:
    {
        GDALColorEntry one, two, three, four, five;
        one.c1 = 2, one.c2 = 32, one.c3 = 227, one.c4 = nTransparency;
        two.c1 = 50, two.c2 = 154, two.c3 = 240, two.c4 = nTransparency;
        three.c1 = 0, three.c2 = 242, three.c3 = 242, three.c4 = nTransparency;
        four.c1 = 50, four.c2 = 219, four.c3 = 110, four.c4 = nTransparency;
        five.c1 = 32, five.c2 = 204, five.c3 = 16, five.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &one, 93, &two);
        colorTable.CreateColorRamp(93, &two, 139, &three);
        colorTable.CreateColorRamp(139, &three, 208, &four);
        colorTable.CreateColorRamp(208, &four, 255, &five);
    }
    case CR_Precipitation:
    {
        GDALColorEntry red, yel, gn1, gn2, gb1, gb2, gb3;
        red.c1 = 194, red.c2 = 82, red.c3 = 60, red.c4 = nTransparency;
        yel.c1 = 252, yel.c2 = 240, yel.c3 = 3, yel.c4 = nTransparency;
        gn1.c1 = 123, gn1.c2 = 237, gn1.c3 = 0, gn1.c4 = nTransparency;
        gn2.c1 = 6, gn2.c2 = 212, gn2.c3 = 27, gn2.c4 = nTransparency;
        gb1.c1 = 27, gb1.c2 = 168, gb1.c3 = 124, gb1.c4 = nTransparency;
        gb2.c1 = 24, gb2.c2 = 117, gb2.c3 = 140, gb2.c4 = nTransparency;
        gb3.c1 = 11, gb3.c2 = 44, gb3.c3 = 122, gb3.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &red, 113, &yel);
        colorTable.CreateColorRamp(113, &yel, 142, &gn1);
        colorTable.CreateColorRamp(142, &gn1, 170, &gn2);
        colorTable.CreateColorRamp(170, &gn2, 198, &gb1);
        colorTable.CreateColorRamp(198, &gb1, 227, &gb2);
        colorTable.CreateColorRamp(227, &gb2, 255, &gb3);
        colorTable.SetColorEntry(0, &trans);
    }
    case CR_Slope:
    {
        GDALColorEntry red, grn, grn2, org, yel;
        grn.c1 = 56, grn.c2 = 168, grn.c3 = 0, grn.c4 = nTransparency;
        grn2.c1 = 139, grn2.c2 = 209, grn2.c3 = 0, grn2.c4 = nTransparency;
        org.c1 = 255, org.c2 = 128, org.c3 = 0, org.c4 = nTransparency;
        red.c1 = 255, red.c2 = 34, red.c3 = 0, red.c4 = nTransparency;
        yel.c1 = 255, yel.c2 = 255, yel.c3 = 0, yel.c4 = nTransparency;

        colorTable.CreateColorRamp(1, &grn, 64, &grn2);
        colorTable.CreateColorRamp(64, &grn2, 128, &yel);
        colorTable.CreateColorRamp(128, &yel, 191, &org);
        colorTable.CreateColorRamp(191, &org, 255, &red);
        colorTable.SetColorEntry(0, &trans);
    }
    case CR_SlopeGCD:
    {
        QVector<int> red(10), grn(10), blu(10);
        GDALColorEntry entry1, entry2;
        int index1, index2;

        red[0] = 255, red[1] = 255, red[2] = 255, red[3] = 255, red[4] = 255, red[5] = 255, red[6] = 255, red[7] = 255, red[8] = 161, red[9] = 130;
        grn[0] = 235, grn[1] = 219, grn[2] = 202, grn[3] = 186, grn[4] = 170, grn[5] = 128, grn[6] = 85, grn[7] = 42, grn[8] = 120, grn[9] = 130;
        blu[0] = 176, blu[1] = 135, blu[2] = 97, blu[3] = 59, blu[4] = 0, blu[5] = 0, blu[6] = 0, blu[7] = 0, blu[8] = 120, blu[9] = 130;

        for (int i=0; i<red.size()-1; i++)
        {
            entry1.c1 = red[i], entry1.c2 = grn[i], entry1.c3 = blu[i], entry1.c4 = nTransparency;
            entry2.c1 = red[i+1], entry2.c2 = grn[i+1], entry2.c3 = blu[i+1], entry2.c4 = nTransparency;
            index1 = round((i / red.size()) * 254) + 1;
            index2 = round(((i+1) / red.size()) * 254) + 1;
            if (i+1 == red.size())
            {
                index2 = 255;
            }
            colorTable.CreateColorRamp(index1, &entry1, index2, &entry2);
        }

        colorTable.SetColorEntry(0, &trans);
    }
    }

    return 0;
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
