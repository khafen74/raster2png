#include <QApplication>
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"
#include "renderer_gcdslopedeg.h"
#include "renderer_gcdslopeper.h"
#include "renderer_gcdptdens.h"
#include "renderer_gcderror.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/ras2png/dod7.tif";
    const char *pngPath = "C:/Test/z_crap/ras2png/z_ras2png_out/dod7.png";
    const char *list = "C:/Test/z_crap/ras2png/z_ras2png_out/dod7.png;C:/Test/z_crap/ras2png/z_ras2png_out/dod7_legend.png";
    const char *listOut = "C:/Test/z_crap/ras2png/z_ras2png_out/stacked.png";

    Renderer_StretchStdDev *Renderer1 = new Renderer_StretchStdDev(inputPath, 2.5, CR_LtBlueDkBlue, 255, false, false);
    Renderer1->rasterToPNG(pngPath, 100, 1000);
    Renderer1->printLegend();

    Renderer::stackImages(list, listOut, 100);


    delete(Renderer1);
    qDebug()<<"finished";

    return a.exec();
}
