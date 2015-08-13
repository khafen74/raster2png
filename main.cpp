#include <QApplication>
#include "raster2png.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/ras2png/dem7.tif";
    const char *pngPath = "C:/Test/z_crap/ras2png/z_ras2png_out/dem7.png";
    const char *inPath2 = "C:/Test/z_crap/ras2png/hlsd7.tif";
    const char *pPath2 = "C:/Test/z_crap/ras2png/z_ras2png_out/hlsd7.png";
    const char *list = "C:/Test/z_crap/ras2png/z_ras2png_out/hlsd7.png;C:/Test/z_crap/ras2png/z_ras2png_out/dem7.png";
    const char *listOut = "C:/Test/z_crap/ras2png/z_ras2png_out/dem7stacked.png";

//    Renderer_StretchMinMax *Renderer2 = new Renderer_StretchMinMax(inputPath, CR_DEM, 128);
//    Renderer2->rasterToPNG(pngPath, 100, 1000);
//    Renderer2->setPrecision(2);
//    Renderer2->printLegend();
    Renderer_StretchMinMax *Renderer1 = new Renderer_StretchMinMax(inputPath, CR_DEM, 145);
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
