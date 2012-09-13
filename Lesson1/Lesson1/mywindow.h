#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QColorDialog>

class MyWindow : public QWidget
{
    Q_OBJECT

    QPushButton* button;
    QLabel* label;
    QColorDialog* dialog;


public:
    explicit MyWindow(QWidget *parent = 0);
    
signals:
    
public slots:
    void myAction();
};

#endif // MYWINDOW_H
