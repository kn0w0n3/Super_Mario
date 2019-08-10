/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef SMALLMARIO_H
#define SMALLMARIO_H

#include <QGraphicsItem>
#include <QPixmap>

class SmallMario : public QGraphicsItem
{
public:
     SmallMario(QGraphicsItem *parent = 0);
     ~SmallMario();
    int direction() const;
    int standingDirection() const;
    void addStandingDirection(int standingDirection);
    void addDirection(int direction);
    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    void stand();
    void jump();
    void standShoot();
    void walk();
    void fall();
    bool isFalling();

private:
    enum State {
         Standing = 0,
         StandShoot,
         Walking,
         Jumping,
         Falling
    };

    int m_direction;
    int mCurrentFrame;
    int m_StandingDirection;
    State mState;
    QPixmap mPixmap;
    QPixmap mWalkPixmap;
    QPixmap mStandingPixmap;
    QPixmap mJumpPixmap;
    QPixmap standShootPixmap;
    QPixmap mShrinkPixmap;

};

#endif // SMALLMARIO_H
