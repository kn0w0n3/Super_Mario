/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

class Mushroom : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + mushroomType };
    Mushroom(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    ~Mushroom();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void nextFrame();

signals:
    void marioSizeStatus(int);

private:

    int mCurrentFrame;
    QPixmap mPixmap;
    QRectF mPlatform;
    int mDirection;
    bool up;
    bool right;
    bool down;
    bool right2;
};
#endif // MUSHROOM_H
