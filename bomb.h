/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef BOMB_H
#define BOMB_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Bomb : public QGraphicsItem
{
public:
    enum { Type = UserType + bombType };
    Bomb(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
};
#endif // BOMB_H
