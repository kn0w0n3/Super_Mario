/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef FIREMARIO_H
#define FIREMARIO_H
#include <QGraphicsItem>
#include <QPixmap>

class FireMario : public QGraphicsItem
{
public:
     FireMario(QGraphicsItem *parent = 0);
     ~FireMario();
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
};
#endif // FIREMARIO_H
