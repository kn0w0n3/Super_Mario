/*
 * Author: equati0n
 * Date: December 2016
*/

#include "giantgoomba.h"
#include <QPainter>

GiantGoomba::GiantGoomba(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame12()

{
    setFlag(ItemClipsToShape);
    mPixmap12 = QPixmap(":images/goomba.png");

}

void GiantGoomba::nextFrame12(){

    mCurrentFrame12 += 121;
    if (mCurrentFrame12 >= 1899 ) {
        mCurrentFrame12 = 0;

    }
}

QRectF GiantGoomba::boundingRect() const {
    return QRectF(0,0,110,97);

}

void GiantGoomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap12, mCurrentFrame12, 0,110, 97);
    setTransformOriginPoint(boundingRect().center());
}

int GiantGoomba::type() const {
    return Type;
}
