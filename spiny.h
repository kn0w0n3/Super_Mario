/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef SPINY_H
#define SPINY_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Spiny : public QGraphicsItem
{
public:
    enum { Type = UserType + spinyType };
    Spiny (QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
#endif // SPINY_H
