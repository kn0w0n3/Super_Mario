/*
 * Author: equati0n
 * Date: December 2016
*/

#include "stairblock.h"
#include <QPainter>

StairBlock::StairBlock( int length, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/stairblock.png");
}

void StairBlock::nextFrame() {
    mCurrentFrame += 48;
    if (mCurrentFrame >= 768 ) {
        mCurrentFrame = 0;
    }
}


QRectF StairBlock::boundingRect() const {
    return QRectF(0,0,48*mLength,48);
}

void StairBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 48*mLength; ++i) {
    painter->drawPixmap(i*48,0, mPixmap, mCurrentFrame, 0,48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}

int StairBlock::type() const {
    return Type;
}
