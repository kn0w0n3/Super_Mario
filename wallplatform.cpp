/*
 * Author: equati0n
 * Date: December 2016
*/

#include "wallplatform.h"
#include <QPainter>

WallPlatform::WallPlatform( int length, QGraphicsItem *parent)
    :QGraphicsItem(parent),mCurrentFrame(0), mLength(length)
{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/wallplatform.png");
}

void WallPlatform::nextFrame() {
    mCurrentFrame += 48;
    if (mCurrentFrame >= 768 ) {
        mCurrentFrame = 0;
    }
}

QRectF WallPlatform::boundingRect() const {
    return QRectF(0,0,48* mLength,48);
}

void WallPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(option);
    for(int i = 0; i < 48*mLength; ++i) {
        painter->drawPixmap(i*48,0, mPixmap, mCurrentFrame, 0,48, 48);
    }
    setTransformOriginPoint(boundingRect().center());
}

int WallPlatform::type() const {
    return Type;
}

