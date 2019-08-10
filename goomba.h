/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef GOOMBA_H
#define GOOMBA_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

class Goomba :  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + goombaType };
    Goomba(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void nextFrame();

signals:
    void marioSizeStatus(int);

private:
    int mCurrentFrame3;
    QPixmap mPixmap3;
    QRectF mPlatform;
    int mDirection;

};
#endif // GOOMBA_H
