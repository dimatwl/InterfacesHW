#include "window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(500, 300);
    QVBoxLayout layout;
}
