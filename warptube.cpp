/*
 * Author: equati0n
 * Date: December 2016
*/

#include "warptube.h"
#include <QPainter>
#include <QDebug>

WarpTube::WarpTube(QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame3()
{
    setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/Warp.png");

}

void WarpTube::nextFrame() {

    mCurrentFrame3 += 54;
    if (mCurrentFrame3 >= 862 ) {
        mCurrentFrame3 = 0;
    }

}

QRectF WarpTube::boundingRect() const {

    return QRectF(0,0,70,100);
}

void WarpTube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,70, 100);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int WarpTube::type() const {

    return Type;
}



