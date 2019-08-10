/*
 * Author: equati0n
 * Date: December 2016
*/

#include "spiny.h"
#include <QPainter>

Spiny::Spiny(QRectF platformRect, int direction,QGraphicsItem *parent)
    : QGraphicsItem(parent)
      ,mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/spiny.png");

}

void Spiny::nextFrame(){

    mCurrentFrame += 238;
    if (mCurrentFrame >= 3569 ) {
        mCurrentFrame = 0;
    }
    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

}

QRectF Spiny::boundingRect() const {
    return QRectF(0,0,120,93);

}

void Spiny::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,120, 93);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Spiny::type() const {
    return Type;
}

