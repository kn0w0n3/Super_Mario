/*
 * Author: equati0n
 * Date: December 2016
*/

#include "stretch.h"
#include <QPainter>

Stretch::Stretch(QGraphicsItem *parent): QGraphicsItem(parent)
      ,mCurrentFrame()

{
    setFlag(ItemClipsToShape);
    mPixmap9 = QPixmap(":images/ustretch.png");

}

void Stretch::nextFrame(){

    mCurrentFrame += 141;
    if (mCurrentFrame >= 8180 ) {
        mCurrentFrame = 0;

    }
}

QRectF Stretch::boundingRect() const {
    return QRectF(0,0,135,112);

}

void Stretch::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    painter->drawPixmap(0,0, mPixmap9, mCurrentFrame, 0,135, 112);
    setTransformOriginPoint(boundingRect().center());
}

int Stretch::type() const {
    return Type;
}
