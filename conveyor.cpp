/*
 * Author: equati0n
 * Date: December 2016
*/

#include "conveyor.h"
#include <QPainter>

Conveyor::Conveyor(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame11()

{
    setFlag(ItemClipsToShape);
    mPixmap11 = QPixmap(":images/conveyorR.png");

}

void Conveyor::nextFrame11(){

    mCurrentFrame11 += 193;
    if (mCurrentFrame11 >= 1544 ) {
        mCurrentFrame11 = 0;

    }
}

QRectF Conveyor::boundingRect() const {
    return QRectF(0,0,190,56);

}

void Conveyor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap11, mCurrentFrame11, 0,190, 56);
    setTransformOriginPoint(boundingRect().center());
}
