/*
 * Author: equati0n
 * Date: December 2016
*/

#include "smallmario.h"
#include <QDebug>
#include <QPainter>

SmallMario::SmallMario(QGraphicsItem *parent): QGraphicsItem(parent) ,m_direction(0),mCurrentFrame(),m_StandingDirection(), mState(Standing) {

    setFlag(ItemClipsToShape);
    mWalkPixmap = QPixmap(":images/shrink.png");
    mStandingPixmap = QPixmap(":images/smallMarioStop.png");
    mJumpPixmap = QPixmap(":images/mario_jump.png");
    standShootPixmap = QPixmap(":images/smallMarioStop.png");
    mShrinkPixmap = QPixmap(":images/shrink.png");
    mPixmap = mWalkPixmap;
}
SmallMario::~SmallMario() {

}

void SmallMario::stand() {

    mPixmap = mStandingPixmap;
    mCurrentFrame = 0;
    mState = Standing;
}

void SmallMario::jump() {

    mState = Jumping;
}

void SmallMario::standShoot() {

    mPixmap = standShootPixmap;
    mCurrentFrame = 0;
    mState = StandShoot;
}

void SmallMario::walk() {

    //qDebug() << "Walking..";
    if(mState == Walking) {
        return;
    }

    mPixmap = mWalkPixmap;
    mCurrentFrame = 0;
    mState = Walking;
}

void SmallMario::fall() {

    mState = Falling;
}

bool SmallMario::isFalling() {

    return mState == Falling;
}

int SmallMario::direction() const {

    return m_direction;
}

int SmallMario::standingDirection() const {

    return m_StandingDirection;
}

void SmallMario::nextFrame(){

    mCurrentFrame += 57;
    if (mCurrentFrame >= 1191 ) {
        mCurrentFrame = 0;
    }
}

QRectF SmallMario::boundingRect() const {
    return QRectF(0,0,45,45);
}

void SmallMario::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(0,0, mPixmap, mCurrentFrame, 0,45, 45);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);

}

void SmallMario::addDirection(int direction) {

    if (direction == m_direction)
        return;

    m_direction += direction;

    if (0 != m_direction) {
        if (-1 == m_direction)
            //QTransform matrix flips the image to face the other direction if left key is pressed
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else//moving right restore normal state by assigning an empty Qtransform object which is an idetntity matrix
            setTransform(QTransform());
    }
}
void SmallMario::addStandingDirection(int standingDirection) {

    m_StandingDirection = standingDirection;
}

bool SmallMario::isTouchingFoot(QGraphicsItem *item) {
    //Foot area
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    //qDebug() << "isTouchingFoot:" << rect.intersects(otherRect);
    return rect.intersects(otherRect);
}

bool SmallMario::isTouchingHead(QGraphicsItem *item) {
    //Foot area
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    //qDebug() << "isTouchingHead:" << rect.intersects(otherRect);
    return rect.intersects(otherRect);
}

bool SmallMario::isTouchingPlatform(QGraphicsItem *item) {
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    //qDebug() << rect;
   // qDebug() << otherRect;
    //qDebug() << otherRect.intersects(rect);
   // qDebug() << "isTouchingPlatform:" << rect.intersects(otherRect);
    return rect.intersects(otherRect);
}

