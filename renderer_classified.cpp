#include "renderer_classified.h"

Renderer_Classified::Renderer_Classified(const char *rasterPath,
                                   int classCount,
                                   ColorRamp ramp,
                                   int nTransparency,
                                   bool zeroCenter,
                                   bool zeroNoData):Renderer(rasterPath, ramp, nTransparency, zeroNoData)
{
    nClasses = classCount;
    nOdd = nClasses % 2;

    setZeroCenter(zeroCenter);

    range = adjMax - adjMin;
    interval = range / (nClasses*1.0);
}

void Renderer_Classified::classifyRaster()
{
    for (int i=0; i<nRows; i++)
    {
        pRaster->GetRasterBand(1)->RasterIO(GF_Read, 0, i, nCols, 1, oldRow, nCols, 1, rasterType, 0, 0);

        for (int j=0; j<nCols; j++)
        {
            if (oldRow[j] == noData || oldRow[j] == noData2)
            {
                newRow[j] = 0;
            }
            else
            {
                if (oldRow[j] >= adjMax)
                {
                    newRow[j] = 255;
                }
                else if (oldRow[j] <= adjMin && oldRow[j] > (adjMin - 1.0))
                {
                    newRow[j] = 1;
                }
                else
                {
                    int count = 0;
                    bool found = false;
                    while (!found && count < nClasses)
                    {
                        if (oldRow[j] >= classBreaks[count] && oldRow[j] < classBreaks[count+1])
                        {
                            newRow[j] = floor(((count*1.0) / (nClasses*1.0)) * 254) + 1;
                            found = true;
                        }
                        else
                        {
                            count++;
                        }
                    }
                }
            }
        }

        pTempRaster->GetRasterBand(1)->RasterIO(GF_Write, 0, i, nCols, 1, newRow, nCols, 1, GDT_Byte, 0, 0);

    }
}

void Renderer_Classified::createByteRaster()
{
    setClassBreaks();
    classifyRaster();
}

void Renderer_Classified::setEqualIntervalBreaks()
{
    classBreaks.clear();
    classBreaks.resize(nClasses+1);

    for (int i=0; i<nClasses+1; i++)
    {
        classBreaks[i] = (adjMin + (interval*i));

        if (zeroCenter && nOdd == 0 && i == (nClasses/2))
        {
            classBreaks[i] = 0.0;
        }

        if (i == nClasses)
        {
            classBreaks[i] = adjMax;
        }
    }
}

void Renderer_Classified::setClassBreaks()
{
    setEqualIntervalBreaks();
}

void Renderer_Classified::setZeroCenter(bool bValue)
{
    zeroCenter = bValue;
    if (zeroCenter)
    {
        if (min < 0.0)
        {
            if (fabs(min) > max)
            {
                adjMax = fabs(min);
                adjMin = min;
            }
            else
            {
                adjMin = max * (-1.0);
                adjMax = max;
            }
        }
    }
}
