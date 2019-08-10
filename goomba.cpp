/*
 * Author: equati0n
 * Date: December 2016
*/

#include "goomba.h"
#include "player.h"
#include "smallmario.h"
#include "firemario.h"
#include <QPainter>
#include <QDebug>

Goomba::Goomba(QRectF platformRect, int direction, QGraphicsItem *parent) : QGraphicsItem(parent), mCurrentFrame3(), mPlatform(platformRect), mDirection(direction)
{
    setFlag(ItemClipsToShape);
    mPixmap3 = QPixmap(":images/goombas.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Goomba::nextFrame() {

    mCurrentFrame3 += 54;
    if (mCurrentFrame3 >= 862 ) {
        mCurrentFrame3 = 0;
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

QRectF Goomba::boundingRect() const {

    return QRectF(0,0,52,50);
}

void Goomba::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {

    painter->drawPixmap(0,0, mPixmap3, mCurrentFrame3, 0,52, 50);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Goomba::type() const {

    return Type;
}


