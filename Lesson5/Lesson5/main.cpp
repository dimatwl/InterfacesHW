#include <QApplication>

#include <ball.h>
#include <window.h>

#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game window;
    window.show();

    return a.exec();
}

