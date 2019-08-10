/*
 * Author: equati0n
 * Date: December 2016
*/

#include "turtle.h"
#include "player.h"
#include "smallmario.h"
#include "firemario.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>

Turtle::Turtle(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame6(), mPlatform(platformRect), mDirection(direction)
{
    setFlag(ItemClipsToShape);
    mPixmap6 = QPixmap(":images/turtle.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Turtle::nextFrame() {

    mCurrentFrame6 += 72;
    if (mCurrentFrame6 >= 1420 ) {
        mCurrentFrame6 = 0;
    }

    if(this->pos().x() < mPlatform.x() || this->pos().x() > mPlatform.x()+ mPlatform.width()) {
        mDirection = -mDirection;
        setTransform(QTransform(-mDirection, 0, 0, 1, boundingRect().width(), 0));
    }
    setPos(this->pos().x() + (mDirection*7), this->pos().y());

    //Collision Detection
        QList<QGraphicsItem *> colliding_items = collidingItems();

        //If one of the colliding items is an Enemy, destroy both the bullet and the enemy
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Player)){

                emit marioSizeStatus(0);
                delete colliding_items[i];
                qDebug()<<"Mario deleted small mario added";
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(SmallMario)){

                emit marioSizeStatus(1);
                delete colliding_items[i];
                qDebug()<<"small mario dead";
                delete this;
                return;

            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(FireMario)){

                emit marioSizeStatus(6);
                delete colliding_items[i];
                qDebug()<<"Fire mario deleted small mario added";
                delete this;
                return;
            }
        }
}

QRectF Turtle::boundingRect() const {

    return QRectF(0,0,68,60);
}

void Turtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap6, mCurrentFrame6, 0,68,60);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Turtle::type() const {

    return Type;
}


