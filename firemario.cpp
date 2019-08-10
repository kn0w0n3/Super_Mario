/*
 * Author: equati0n
 * Date: December 2016
*/
#include"firemario.h"
#include <QPainter>

FireMario::FireMario(QGraphicsItem *parent) : QGraphicsItem(parent) ,m_direction(0),mCurrentFrame(),m_StandingDirection(), mState(Standing){

    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":images/firemario.png");
    mStandingPixmap = QPixmap(":images/firemariostop.png");
    mJumpPixmap = QPixmap(":images/mario_jump.png");
    standShootPixmap = QPixmap(":images/firemariostop.png");
    mPixmap = mWalkPixmap;
}

FireMario::~FireMario(){

}

void FireMario::stand(){

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void FireMario::jump(){
    mState = Jumping;
}

void FireMario::standShoot(){

    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void FireMario::walk(){

    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void FireMario::fall(){

    mState = Falling;
}

bool FireMario::isFalling(){

    return mState == Falling;
}

int FireMario::direction() const{

    return m_direction;
}

int FireMario::standingDirection() const{

    return m_StandingDirection;
}

void FireMario::nextFrame(){

    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191 ) {
        mCurrentFrame = 0;
    }
}

QRectF FireMario::boundingRect() const{

    return QRectF(0,0,45,73);
}

void FireMario::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,45, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void FireMario::addDirection(int direction){

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction){
        if (-1 == m_direction)

            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}

void FireMario::addStandingDirection(int standingDirection){

    m_StandingDirection = standingDirection;
}

bool FireMario::isTouchingFoot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool FireMario::isTouchingHead(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool FireMario::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

