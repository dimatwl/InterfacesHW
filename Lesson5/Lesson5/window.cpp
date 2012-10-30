#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    game(),
    view(&game)
{
    this->setCentralWidget(&game);
}
