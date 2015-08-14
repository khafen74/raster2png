#include "raster2png.h"

Raster2PNG::Raster2PNG(int argc, char *argv[])
{
    init(argc, argv);
}

int Raster2PNG::init(int argc, char *argv[])
{
    GDALAllRegister();

    mStdDev = 0.0;
    m_bLegend = false, m_bZeroCenter = false, m_bZeroNoData = false;
    mColorRamp = CR_BlackWhite;
    m_nQuality = 100, m_nLongAxisPixels = 1000, m_nClasses = 0, m_nTransparency = 255;

    QString value;

    if (argc < 3 || argc > 11)
        ;//arguments error
    else
    {
        mInputRaster = argv[2];
        mOutputPng = argv[3];
        mStyle = GetRenderStyleFromString(argv[1]);
    }

    if (argc > 3)
        mColorRamp = GetColorRampFromString(argv[4]);
    if (argc > 4)
    {
        value = QString::fromUtf8(argv[5]);
        m_nTransparency = value.toInt();
        if (m_nTransparency < 0 || m_nTransparency > 255)
        {
            ;//transparency value out of range
        }
    }
    if (argc > 5)
    {
        value = QString::fromUtf8(argv[6]);
        if (value.toDouble() < 0.0)
        {
            ;//class/std dev error
        }
        else
        {
            if (mStyle == RS_Classified)
                m_nClasses = value.toInt();
            else if (mStdDev == RS_Stretched)
                mStdDev = value.toDouble();
        }
    }
    if (argc > 6)
    {
        value = QString::fromUtf8(argv[7]);
        m_bLegend = value.toInt();
    }
    if (argc > 7)
    {
        value = QString::fromUtf8(argv[8]);
        m_nQuality = value.toInt();
        if (m_nQuality > 100 || m_nQuality <-1)
        {
            ;//quality range error
        }
    }
    if (argc > 8)
    {
        value = QString::fromUtf8(argv[9]);
        m_nLongAxisPixels = value.toInt();
    }
    if (argc > 9)
    {
        value = QString::fromUtf8(argv[10]);
        m_bZeroCenter = value.toInt();
    }
    if (argc > 10)
    {
        value = QString::fromUtf8(argv[11]);
        m_bZeroNoData = value.toInt();
    }
}

int Raster2PNG::run()
{
    if (mStyle == RS_Classified)
    {
        CreateClassifiedPNG();
    }
    else if (mStyle == RS_Stretched)
    {
        CreateStretchedPNG();
    }
    else if (mStyle == RS_Brightness)
    {
        CreateBrightnessPNG();
    }
    else
    {
        //error
    }
}

int Raster2PNG::CreateStretchedPNG()
{
    if (mStdDev > 0.0)
    {
        Renderer_StretchStdDev pngRender(mInputRaster, mStdDev, mColorRamp, m_nTransparency, m_bZeroCenter, m_bZeroNoData);
        pngRender.rasterToPNG(mOutputPng, m_nQuality, m_nLongAxisPixels);
        if (m_bLegend)
        {
            pngRender.printLegend();
        }
    }
    else
    {
        Renderer_StretchMinMax pngRender(mInputRaster, mColorRamp, m_nTransparency, m_bZeroCenter, m_bZeroNoData);
        pngRender.rasterToPNG(mOutputPng, m_nQuality, m_nLongAxisPixels);
        if (m_bLegend)
        {
            pngRender.printLegend();
        }
    }
}

int Raster2PNG::CreateClassifiedPNG()
{
    Renderer_Classified pngRender(mInputRaster, m_nClasses, mColorRamp, m_nTransparency, m_bZeroCenter, m_bZeroNoData);
    pngRender.rasterToPNG(mOutputPng, m_nQuality, m_nLongAxisPixels);
    if (m_bLegend)
    {
        pngRender.printLegend();
    }
}

int Raster2PNG::CreateBrightnessPNG()
{
    Renderer_ByteData pngRender(mInputRaster, mColorRamp, m_nTransparency);
    pngRender.rasterToPNG(mOutputPng, m_nQuality, m_nLongAxisPixels);
    if (m_bLegend)
    {
        pngRender.printLegend();
    }
}

ColorRamp Raster2PNG::GetColorRampFromString(const char *ramp)
{
    QString qsRamp(ramp);

        if (QString::compare(qsRamp , "BlackWhite", Qt::CaseInsensitive) == 0)
            return CR_BlackWhite;
        else if (QString::compare(qsRamp , "DEM", Qt::CaseInsensitive) == 0)
            return CR_DEM;
        else if (QString::compare(qsRamp , "DoD", Qt::CaseInsensitive) == 0)
            return CR_DoD;
        else if (QString::compare(qsRamp , "GrainSize", Qt::CaseInsensitive) == 0)
            return CR_GrainSize;
        else if (QString::compare(qsRamp , "GreenBlue", Qt::CaseInsensitive) == 0)
            return CR_GreenBlue;
        else if (QString::compare(qsRamp , "LtBlueDkBlue", Qt::CaseInsensitive) == 0)
            return CR_LtBlueDkBlue;
        else if (QString::compare(qsRamp , "PartialSpectrum", Qt::CaseInsensitive) == 0)
            return CR_PartialSpectrum;
        else if (QString::compare(qsRamp , "Precipitation", Qt::CaseInsensitive) == 0)
            return CR_Precipitation;
        else if (QString::compare(qsRamp , "Slope", Qt::CaseInsensitive) == 0)
            return CR_Slope;
        else if (QString::compare(qsRamp , "SlopeGCD", Qt::CaseInsensitive) == 0)
            return CR_SlopeGCD;
        else if (QString::compare(qsRamp , "CR_WhiteRed", Qt::CaseInsensitive) == 0)
            return CR_WhiteRed;
        else
            return CR_BlackWhite;
}

RenderStyle Raster2PNG::GetRenderStyleFromString(const char *style)
{
    QString qsStyle(style);

    if (QString::compare(qsStyle, "Classified", Qt::CaseInsensitive) == 0)
        return RS_Classified;
    else if (QString::compare(qsStyle, "Stretched", Qt::CaseInsensitive) == 0)
        return RS_Stretched;
    else if (QString::compare(qsStyle, "Brightness", Qt::CaseInsensitive) == 0)
        return RS_Brightness;
    else
        return RS_Stretched;
}

void Raster2PNG::PrintHelp()
{
    std::cout<< "\n Raster2PNG: convert raster datasets to PNG images";
    std::cout<< "\n\n Usage: raster2png <style> <input_raster_path> <output_png_path>";
    std::cout<< "\n                           <color_ramp> <transparency> <bin_stretch>";
    std::cout<< "\n                           <legend> <quality> <long_axis_px>";
    std::cout<< "\n                           <zero_center> <zero_nodata>";
    std::cout<< "\n     style                 Must be one of 'Classified', 'Stretched',";
    std::cout<< "\n                           or 'Brightness' (required)";
    std::cout<< "\n     input_raster_path     Path to GDAL compatable raster (required)";
    std::cout<< "\n     output_png_path       Path to write output png file (required)";
    std::cout<< "\n     color_ramp            String naming color ramp style,";
    std::cout<< "\n                           see options below, default=BlackWhite";
    std::cout<< "\n     transparency          0-255 transparency of output PNG, 255=opaque,";
    std::cout<< "\n                           default=255";
    std::cout<< "\n     bin_stretch           Number of classes or std dev stretch value,";
    std::cout<< "\n                           value of 0 results in min-max stretch, default=0";
    std::cout<< "\n     legend                Print legend, 0=false , 1=true, default=0";
    std::cout<< "\n     quality               0-100 png quality, default=100";
    std::cout<< "\n     long_axis_px          Number of pixels on longest side of out put image,";
    std::cout<< "\n                           default=1000";
    std::cout<< "\n     zero_center           Center data on zero, 0=false , 1=true, default=0";
    std::cout<< "\n     zero_nodata           Display zero values as NoData, 0=false , 1=true,";
    std::cout<< "\n                           default=0";
    std::cout<< "\n\n";
    std::cout<< "\n     color ramp values     BlackWhite, DEM, DoD, GrainSize, GreenBlue,";
    std::cout<< "\n                           LtBlueDkBlue, PartialSpectrum, Precipitation,";
    std::cout<< "\n                           Slope, SlopeGCD, WhiteRed";
    std::cout<< "\n\n";
}
