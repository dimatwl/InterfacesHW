#include "ball.h"

Ball::Ball(quint32 radius, QPoint center) : radius(radius), center(center)
{
    setFlag(ItemIsMovable);
}
