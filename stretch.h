/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef STRETCH_H
#define STRETCH_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Stretch : public QGraphicsItem
{
public:
    enum { Type = UserType + stretchType };
    Stretch(QGraphicsItem *parent = 0);
    int type() const;
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    int mCurrentFrame;
    QPixmap mPixmap9;
};
#endif // STRETCH_H
