/*
 * Author: equati0n
 * Date: December 2016
*/

#include "player.h"
#include <QPainter>

Player::Player(QGraphicsItem *parent) : QGraphicsItem(parent) ,m_direction(0),mCurrentFrame(),m_StandingDirection(), mState(Standing){

    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":images/mario.png");
    mStandingPixmap = QPixmap(":images/mariostop.png");
    mJumpPixmap = QPixmap(":images/mario_jump.png");
    standShootPixmap = QPixmap(":images/mariostop.png");
    mPixmap = mWalkPixmap;
}

Player::~Player(){

}

void Player::stand(){

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void Player::jump(){
    mState = Jumping;
}

void Player::standShoot(){

    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void Player::walk(){

    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void Player::fall(){

    mState = Falling;
}

bool Player::isFalling(){

    return mState == Falling;
}

int Player::direction() const{

    return m_direction;
}

int Player::standingDirection() const{

    return m_StandingDirection;
}

void Player::nextFrame(){

    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191 ) {
        mCurrentFrame = 0;
    }
}

QRectF Player::boundingRect() const{

    return QRectF(0,0,45,73);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,45, 73);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

void Player::addDirection(int direction){

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

void Player::addStandingDirection(int standingDirection){

    m_StandingDirection = standingDirection;
}

bool Player::isTouchingFoot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());   
    return rect.intersects(otherRect);
}

