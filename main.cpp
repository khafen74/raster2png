#include <QCoreApplication>
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"
#include "renderer_gcdslopedeg.h"
#include "renderer_gcdslopeper.h"
#include "renderer_gcdptdens.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/ptdens1.img";
    const char *pngPath = "C:/Test/z_crap/ptdenspng.png";

    qDebug()<<"setting up renderer";
    Renderer_GCDPtDens *Renderer1 = new Renderer_GCDPtDens(inputPath);
    qDebug()<<"renderer set up";
    Renderer1->rasterToPNG(pngPath, 100, 2000);
    qDebug()<<"png printed";

    delete(Renderer1);
    qDebug()<<"renderer deleted";

    return a.exec();
}
