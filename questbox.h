/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef QUESTBOX_H
#define QUESTBOX_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class QuestBox : public QGraphicsItem
{
public:
    enum { Type = UserType + questBoxType };
    QuestBox(int length,QGraphicsItem *parent = 0);
    void nextFrame4();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame4;
    QPixmap mPixmap4;
    int mLength;
};
#endif // QUESTBOX_H

