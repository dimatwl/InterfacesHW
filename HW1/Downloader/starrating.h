#ifndef STARRATING_H
#define STARRATING_H

#include <QMetaType>
#include <QPainter>
#include <QPolygonF>
#include <QPalette>

#include <math.h>

class StarRating
{
public:
    enum EditMode { Editable, ReadOnly };

    StarRating(int starCount = 1, int maxStarCount = 5);

    void paint(QPainter *painter, const QRect &rect,
               const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;
    int starCount() const { return myStarCount; }
    int maxStarCount() const { return myMaxStarCount; }
    void setStarCount(int starCount) { myStarCount = starCount; }
    void setMaxStarCount(int maxStarCount) { myMaxStarCount = maxStarCount; }

private:
    QPolygonF starPolygon;
    QPolygonF diamondPolygon;
    int myStarCount;
    int myMaxStarCount;
    int PaintingScaleFactor;
};

Q_DECLARE_METATYPE(StarRating)

#endif // STARRATING_H
