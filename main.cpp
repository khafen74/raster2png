#include <QApplication>
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"
#include "renderer_gcdslopedeg.h"
#include "renderer_gcdslopeper.h"
#include "renderer_gcdptdens.h"
#include "renderer_gcderror.h"
#include "renderer_bytedata.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/ras2png/dem1.tif";
    const char *pngPath = "C:/Test/z_crap/ras2png/z_ras2png_out/dem1.png";
    const char *inPath2 = "C:/Test/z_crap/ras2png/hlsd1.tif";
    const char *pPath2 = "C:/Test/z_crap/ras2png/z_ras2png_out/hlsd1.png";
    const char *list = "C:/Test/z_crap/ras2png/z_ras2png_out/hlsd1.png;C:/Test/z_crap/ras2png/z_ras2png_out/dem1.png;C:/Test/z_crap/ras2png/z_ras2png_out/dem1_legend.png";
    const char *listOut = "C:/Test/z_crap/ras2png/z_ras2png_out/stacked.png";

    Renderer_StretchMinMax *Renderer1 = new Renderer_StretchMinMax(inputPath, CR_DEM, 128, false, false);
    Renderer1->rasterToPNG(pngPath, 100, 1000);
    Renderer1->setPrecision(2);
    Renderer1->printLegend();

    Renderer_ByteData *Renderer2 = new Renderer_ByteData(inPath2);
    Renderer2->rasterToPNG(pPath2, 100, 1000);

    Renderer::stackImages(list, listOut, 100);


    delete(Renderer1);
    qDebug()<<"finished";

    return a.exec();
}
