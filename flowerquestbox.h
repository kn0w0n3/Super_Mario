/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef FLOWERQUESTBOX_H
#define FLOWERQUESTBOX_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class FlowerQuestBox : public QGraphicsItem
{
public:
    enum { Type = UserType + flowerQuestBoxType };
    FlowerQuestBox(int length,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap;
    int mLength;
};
#endif // FLOWERQUESTBOX_H
