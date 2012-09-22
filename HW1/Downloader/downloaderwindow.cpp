#include "downloaderwindow.h"

DownloaderWindow::DownloaderWindow(QWidget *parent) :
    QMainWindow(parent)
{
    myTable = new QTableWidget(5,1);
    this->setCentralWidget(new QLabel("Hello world", this));
    //menuBar()->addMenu(tr("&File"));
    Config::Instance();
}

void DownloaderWindow::onClose() {
    Config::Instance().saveToDB();
}
