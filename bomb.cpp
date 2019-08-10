/*
 * Author: equati0n
 * Date: December 2016
*/

#include "bomb.h"
#include <QPainter>

Bomb::Bomb(QRectF platformRect, int direction,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/bomb.png");

}

void Bomb::nextFrame(){

    mCurrentFrame += 129;
    if (mCurrentFrame >= 2579 ) {
        mCurrentFrame = 0;
    }
    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

}

QRectF Bomb::boundingRect() const {
    return QRectF(0,0,130,123);

}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,130, 123);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Bomb::type() const {
    return Type;
}

