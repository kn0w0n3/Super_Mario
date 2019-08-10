/*
 * Author: equati0n
 * Date: December 2016
*/

#include "fireball.h"
#include "goomba.h"
#include "warptube.h"
#include "turtle.h"
#include <QPainter>
#include <QGraphicsScene>
#include <typeinfo>

FireBall::FireBall(int standingDirection, QGraphicsItem *parent): QGraphicsItem(parent),m_StandingDirection(standingDirection),mState(), mCurrentFrame() {

    setFlag(ItemClipsToShape);
    mPixmap = QPixmap(":images/fireBall.png");
    mBouncingPixmap = QPixmap(":images/fireballx2.png");

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timer->start(100);
    inPosition = false;
}

FireBall::~FireBall(){

}

void FireBall::moveBullet(){

    if(this->pos().y() > 600){

        inPosition = true;

    }else{

        inPosition = false;
    }

    if(inPosition){

        mPixmap = mBouncingPixmap;
        mCurrentFrame += 23;
        if (mCurrentFrame >= 322){
            mCurrentFrame = 0;
        }

        if(m_StandingDirection == -1){

            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(),0));
            setPos(this->pos().x() + (m_StandingDirection * 100), this->pos().y());
        }
        else if(m_StandingDirection == 1){

            setPos(this->pos().x() + (m_StandingDirection * 100), this->pos().y());
        }
        else{

            setPos(this->pos().x() + (m_StandingDirection * 100), this->pos().y());
        }

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Goomba)){

                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(WarpTube)){

                emit increaseTheScore(1);
                emit fireballCollision();
                delete this;
                return;
            }
        }
        if ((pos().x() + boundingRect().width() > 8000)||(pos().x() + boundingRect().width() < 0)){
            scene()->removeItem(this);
            delete this;
            qDebug()<<"Fireball deleted";
        }
    }
    else if(!inPosition){

        inPosition = false;

        if(m_StandingDirection == -1){

            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(),0));
            setPos(this->pos().x() + (m_StandingDirection*80), this->pos().y() - (m_StandingDirection*80));
        }
        else if(m_StandingDirection == 1){

            setPos(this->pos().x() + (m_StandingDirection*80), this->pos().y() + (m_StandingDirection*80));
        }
        else{

            setPos(this->pos().x() + (m_StandingDirection*80), this->pos().y() + (m_StandingDirection*80));
        }

        QList<QGraphicsItem *> colliding_items = collidingItems();

        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Goomba)){

                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Turtle)){

                emit increaseTheScore(1);
                emit collideGoomba();
                delete colliding_items[i];
                delete this;
                return;
            }
        }
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(WarpTube)){

                emit increaseTheScore(1);
                emit fireballCollision();
                delete this;
                return;
            }
        }

        if ((pos().x() + boundingRect().width() > 8000)||(pos().x() + boundingRect().width() < 0)){
            scene()->removeItem(this);
            delete this;
            qDebug()<<"Fireball deleted";
        }
    }
}

QRectF FireBall::boundingRect() const{
    return QRectF(0,0,23,81);
}

void FireBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,23, 81);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int FireBall::type() const {

    return Type;
}

