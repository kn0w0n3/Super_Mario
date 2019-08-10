/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef PIRANHA_H
#define PIRANHA_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class Piranha : public QGraphicsItem
{
public:
    enum { Type = UserType + piranhaType };
    Piranha(QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame7;
    QPixmap mPixmap7;

};
#endif // PIRANHA_H
