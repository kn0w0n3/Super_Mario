/*
 * Author: equati0n
 * Date: December 2016
*/

#include "flag.h"
#include <QPainter>

Flag::Flag(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame()

{
    setFlag(ItemClipsToShape);
    mPixmap8 = QPixmap(":images/mflag.png");

}

void Flag::nextFrame(){

    mCurrentFrame += 322;
    if (mCurrentFrame >= 5439 ) {
        mCurrentFrame = 0;

    }
}

QRectF Flag::boundingRect() const {
    return QRectF(0,0,115,84);

}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap8, mCurrentFrame, 0,115, 84);
    setTransformOriginPoint(boundingRect().center());
}
int Flag::type() const
{
  return Type;
}
