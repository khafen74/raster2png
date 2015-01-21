#include "renderer_stretchstddev.h"

Renderer_StretchStdDev::Renderer_StretchStdDev(const char *inputRasterPath,
                                           double stDevStretch,
                                           ColorRamp ramp,
                                           int nTransparency,
                                           bool zeroCenter,
                                           bool zeroNoData):Renderer(inputRasterPath, ramp, nTransparency, zeroNoData)
{
    setZeroCenter(zeroCenter);
    sdStretch = stDevStretch;

    sdMin = adjMean - (sdStretch *stdev);
    if (sdMin < minCalc)
    {
        sdMin = minCalc;
    }
    sdMax = adjMean + (sdStretch * stdev);
    if (sdMax > maxCalc)
    {
        sdMax = maxCalc;
    }
    range = sdMax - sdMin;
}

void Renderer_StretchStdDev::createByteRaster()
{
    double scaled;
    int byte;

    for (int i=0; i<nRows; i++)
    {
        pRaster->GetRasterBand(1)->RasterIO(GF_Read, 0, i, nCols, 1, oldRow, nCols, 1, rasterType, 0, 0);

        for (int j=0; j<nCols; j++)
        {
            if (oldRow[j] == noData || oldRow[j] == noData2)
            {
                newRow[j] = 0;
            }

            else if (oldRow[j]+corVal <= sdMin)
            {
                newRow[j] = 1;
            }
            else if (oldRow[j]+corVal >= sdMax)
            {
                newRow[j] = 255;
            }
            else
            {
                scaled = 1.0 - fabs(((sdMax) - (oldRow[j]+corVal)) / range);
                byte = round(scaled * 254) + 1;
                newRow[j] = byte;
            }
        }

        pTempRaster->GetRasterBand(1)->RasterIO(GF_Write, 0, i, nCols, 1, newRow, nCols, 1, GDT_Byte, 0, 0);
    }
}

void Renderer_StretchStdDev::setZeroCenter(bool bValue)
{
    zeroCenter = bValue;

    if (zeroCenter)
    {
        if (max > 0.0)
        {
            if (min < 0.0)
            {
                if (fabs(min) > max)
                {
                    adjMax = fabs(min);
                    maxCalc = 2.0 * fabs(min);
                    minCalc = 0.0;
                }
                else
                {
                    adjMin = max * (-1.0);
                    maxCalc = max * 2.0;
                    minCalc = 0.0;
                }
            }
            else
            {
                adjMin = max * (-1.0);
                maxCalc = max * 2.0;
                minCalc = 0.0;
            }
        }
        corVal = fabs(adjMin);
        adjMean = corVal;
    }
    else
    {
        if (min < 0.0)
        {
            corVal = fabs(min);
            maxCalc = max + corVal;
            minCalc = 0.0;
        }
        else if (max < 0.0)
        {
            maxCalc = fabs(max) + fabs(min);
            minCalc = fabs(min);
            corVal = fabs(min);
        }
        else
        {
            corVal = 0.0;
            maxCalc = max, minCalc = min;
        }
        adjMean += corVal;
    }
}
