/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef BRICKPLATFORM_H
#define BRICKPLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class BrickPlatform : public QGraphicsItem
{
public:
    enum { Type = UserType + brickPlatformType };
    BrickPlatform( int length, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
    int mDirection;
};
#endif // BRICKPLATFORM_H
