/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef COIN_H
#define COIN_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Coin : public QGraphicsItem
{

public:
    enum { Type = UserType + coinType };
    Coin(QGraphicsItem *parent = 0);
    void nextFrame2();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:

    int mCurrentFrame2;
    QPixmap mPixmap2;

};

#endif // COIN_H
