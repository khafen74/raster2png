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

    const char *inputPath = "C:/Test/z_crap/ras2png/error4.tif";
    const char *pngPath = "C:/Test/z_crap/ras2png/z_ras2png_out/error4.png";
    const char *inPath2 = "C:/Test/z_crap/ras2png/hlsd7.tif";
    const char *pPath2 = "C:/Test/z_crap/ras2png/z_ras2png_out/hlsd7.png";
    const char *list = "C:/Test/z_crap/ras2png/z_ras2png_out/error4.png;C:/Test/z_crap/ras2png/z_ras2png_out/error4_legend.png";
    const char *listOut = "C:/Test/z_crap/ras2png/z_ras2png_out/error4stacked.png";

//    Renderer_StretchMinMax *Renderer2 = new Renderer_StretchMinMax(inputPath, CR_DEM, 128);
//    Renderer2->rasterToPNG(pngPath, 100, 1000);
//    Renderer2->setPrecision(2);
//    Renderer2->printLegend();
    Renderer_GCDError *Renderer1 = new Renderer_GCDError(inputPath);
    Renderer1->rasterToPNG(pngPath, 100, 1000);
    //Renderer1->setPrecision(2);
    Renderer1->printLegend();

    //Renderer_ByteData *Renderer2 = new Renderer_ByteData(inPath2);
    //Renderer2->rasterToPNG(pPath2, 100, 1000);

    Renderer::stackImages(list, listOut, 100);


    delete(Renderer1);
    qDebug()<<"finished";

    return a.exec();
}
