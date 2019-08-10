/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef TURTLE_H
#define TURTLE_H
#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <QGraphicsScene>

class Turtle : public QObject, public QGraphicsItem
{
  Q_OBJECT
public:
    enum { Type = UserType + turtleType };
    Turtle(QRectF platformRect, int direction,QGraphicsItem *parent = 0);
    //void nextFrame6();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

public slots:
    void nextFrame();

signals:
    void marioSizeStatus(int);

private:

    int mCurrentFrame6;
    QPixmap mPixmap6;
    QRectF mPlatform;
    int mDirection;
};
#endif // TURTLE_H
