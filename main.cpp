#include <QCoreApplication>
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"
#include "renderer_gcdslopedeg.h"
#include "renderer_gcdslopeper.h"
#include "renderer_gcdptdens.h"
#include "renderer_gcderror.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/ras2png/dod7.tif";
    const char *pngPath = "C:/Test/z_crap/ras2png/z_ras2png_out/dod7.png";

    Renderer_Classified *Renderer1 = new Renderer_Classified(inputPath, 20, CR_DoD, 255, true, true);
    Renderer1->rasterToPNG(pngPath, 100, 1000);


    delete(Renderer1);
    qDebug()<<"finished";

    return a.exec();
}
