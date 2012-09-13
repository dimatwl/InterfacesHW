#include "mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QWidget(parent)
{
    button = new QPushButton("push", this);
    label = new QLabel("???", this);
    dialog = new QColorDialog(this);


    setLayout(new QVBoxLayout());
    layout()->addWidget(button);
    layout()->addWidget(label);

    connect(button, SIGNAL(clicked()), this, SLOT(myAction()));
}

void MyWindow::myAction()
{
    dialog->exec();
    label->setText(dialog->currentColor().name());
    qDebug() << "slot";
}
