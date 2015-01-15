#ifndef STRETCHRENDERERMINMAX_H
#define STRETCHRENDERERMINMAX_H

#include "renderer.h"

class Renderer_StetchMinMax : public Renderer
{
public:
    Renderer_StetchMinMax(const char *inputRasterPath,
                          ColorRamp ramp = CR_BlackWhite,
                          int nTransparency = 255,
                          bool zeroCenter = FALSE,
                          bool zeroNoData = FALSE);

protected:
    double corVal, maxCalc, minCalc;

    void createByteRaster();
    void setZeroCenter(bool bValue);
};

#endif // STRETCHRENDERERMINMAX_H