#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include <game.h>

class Window : public QMainWindow
{
    Q_OBJECT

    Game game;
    QGraphicsView view;

public:
    explicit Window(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // WINDOW_H
