#include <QtGui/QApplication>
#include "mywindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyWindow mw;
    mw.show();

    return a.exec();
}
