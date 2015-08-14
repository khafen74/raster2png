#include <QApplication>
#include "raster2png.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try
    {
        Raster2PNG converter(argc, argv);
        //converter.PrintHelp();

        int result = converter.run();
    }
    catch(std::exception &e)
    {
        std::cerr << "Error: " <<e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    //return a.exec();
    qApp->quit();
}
