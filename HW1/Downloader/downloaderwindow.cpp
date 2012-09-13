#include "downloaderwindow.h"

DownloaderWindow::DownloaderWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setCentralWidget(new QLabel("Hello world", this));
}
