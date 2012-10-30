#ifndef BALL_H
#define BALL_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPoint>

class Ball : public QGraphicsItem
{
    quint32 radius;
    QPoint center;
public:
    Ball(quint32 radius, QPoint center);

    QRectF boundingRect() const
    {
        qreal penWidth = 1;
        return QRectF(-radius, -radius,
                      radius, radius);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget)
    {
        painter->drawEllipse(center, radius, radius);
    }
};

#endif // BALL_H
