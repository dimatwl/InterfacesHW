#ifndef DOWNLOADERWINDOW_H
#define DOWNLOADERWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidget>

#include "config.h"

class DownloaderWindow : public QMainWindow
{
    Q_OBJECT

    QTableWidget* myTable;
public:
    explicit DownloaderWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void onClose();
};

#endif // DOWNLOADERWINDOW_H
