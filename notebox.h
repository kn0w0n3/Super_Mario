/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef NOTEBOX_H
#define NOTEBOX_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"

class NoteBox : public QGraphicsItem
{
public:
    enum { Type = UserType + noteBoxType };
    NoteBox(int length,QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
private:

    int mCurrentFrame;
    QPixmap mPixmap10;
    int mLength;
};
#endif // NOTEBOX_H
