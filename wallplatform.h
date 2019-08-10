/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef WALLPLATFORM_H
#define WALLPLATFORM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class WallPlatform : public QGraphicsItem
{
public:
    enum { Type = UserType + wallPlatformType };
    WallPlatform ( int length, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
#endif // WALLPLATFORM_H
