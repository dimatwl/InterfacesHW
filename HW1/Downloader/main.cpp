#include <QtGui/QApplication>
#include "downloaderwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DownloaderWindow dw;
    dw.show();

    return a.exec();
}

