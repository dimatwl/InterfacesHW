#include "downloaderwindow.h"

DownloaderWindow::DownloaderWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->resize(500, 300);
    myTable = new QTableWidget(1,5);
    this->setCentralWidget(myTable);
    menuBar()->addMenu("File");
    menuBar()->addMenu("Help");
    //myTable->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    Config::Instance();
}

void DownloaderWindow::onClose() {
    Config::Instance().saveToDB();
}
