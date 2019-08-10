/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef STAIRBLOCK_H
#define STAIRBLOCK_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class StairBlock : public QGraphicsItem
{
public:
    enum { Type = UserType + stairBlockType };
    StairBlock ( int length, QGraphicsItem *parent = 0);
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
#endif // STAIRBLOCK_H
