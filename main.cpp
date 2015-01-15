#include <QCoreApplication>
#include "renderer_classified.h"
#include "renderer_stretchminmax.h"
#include "renderer_stretchstddev.h"
#include "renderer_gcdslopedeg.h"
#include "renderer_gcdslopeper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    GDALAllRegister();

    const char *inputPath = "C:/Test/z_crap/slope.tif";
    const char *pngPath = "C:/Test/z_crap/slopepng.png";

    qDebug()<<"setting up renderer";
    Renderer_GCDSlopePer *Renderer1 = new Renderer_GCDSlopePer(inputPath);
    qDebug()<<"renderer set up";
    Renderer1->rasterToPNG(pngPath, 100, 700);
    qDebug()<<"png printed";

    delete(Renderer1);
    qDebug()<<"renderer deleted";

    return a.exec();
}
