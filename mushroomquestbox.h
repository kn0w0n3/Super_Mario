/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef MUSHROOMQUESTBOX_H
#define MUSHROOMQUESTBOX_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class MushroomQuestBox : public QGraphicsItem
{
public:
    enum { Type = UserType + mushroomQuestBoxType };
    MushroomQuestBox(int length,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

private:
    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
#endif // MUSHROOMQUESTBOX_H
