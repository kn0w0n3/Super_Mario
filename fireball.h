/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsItem>
#include <QPixmap>
#include "objecttype.h"
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QMediaPlayer>

class FireBall: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum { Type = UserType + fireBallType };
    FireBall(int standingDirection, QGraphicsItem *parent = 0);
    ~FireBall();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

signals:
    void increaseTheScore(int);
    void changeFireball(int);
    void fireballCollision();
    void collideGoomba();
public slots:
    void moveBullet();

private:

    enum State {
        notBouncing = 0,
        bouncing,
    };

    int m_StandingDirection;
    State mState;
    int mCurrentFrame;
    QPixmap mPixmap;
    QPixmap mBouncingPixmap;
    QRectF mPlatform;
    int m_CrouchingDirection;
    bool inPosition;
    QTimer *timer;
};
#endif // FIREBALL_H
