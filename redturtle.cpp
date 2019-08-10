/*
 * Author: equati0n
 * Date: December 2016
*/

#include "redturtle.h"
#include <QPainter>

RedTurtle::RedTurtle(QRectF platformRect, int direction,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/redt.png");

}

void RedTurtle::nextFrame(){

    mCurrentFrame += 179;
    if (mCurrentFrame >= 3521 ) {
        mCurrentFrame = 0;
    }
    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

}

QRectF RedTurtle::boundingRect() const {
    return QRectF(0,0,130,146);

}

void RedTurtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,130, 146);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int RedTurtle::type() const {
    return Type;
}

