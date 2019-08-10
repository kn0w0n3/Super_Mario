/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef GIANTGOOMBA_H
#define GIANTGOOMBA_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class GiantGoomba : public QGraphicsItem
{
public:
    enum { Type = UserType + giantGoombaType };
    GiantGoomba(QGraphicsItem *parent = 0);
    int type() const;
    void nextFrame12();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame12;
    QPixmap mPixmap12;
};
#endif // GIANTGOOMBA_H
