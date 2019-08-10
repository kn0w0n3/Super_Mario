/*
 * Author: equati0n
 * Date: December 2016
*/

#include "flower.h"
#include "firemario.h"
#include "player.h"
#include "smallmario.h"
#include <QPainter>
#include <QDebug>

Flower::Flower(QRectF platformRect, int direction,QGraphicsItem *parent): QGraphicsItem(parent),mCurrentFrame(),mPlatform(platformRect), mDirection(direction)

{
    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/flower.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
    up= true;
    down = true;
    right = true;
    right2 = false;

}

void Flower::nextFrame(){

    if(up) {
        if(this->pos().y() > mPlatform.y()-40) {

            setPos(this->pos().x(), this->pos().y() - (mDirection *5));
        }
    }
    if(right){
        if(this->pos().y() == mPlatform.y() -42) {

            up = false;

        }
    }

    //Collision Detection
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Player)){

            emit marioSizeStatusf(4);
            delete colliding_items[i];

            delete this;
            return;
        }
    }

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(FireMario)){

            emit marioSizeStatusf(5);

            //delete colliding_items[i];
            delete this;
            return;
        }
    }
}

QRectF Flower::boundingRect() const {
    return QRectF(0,0,70,50);

}

void Flower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,70, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

int Flower::type() const {
    return Type;
}
