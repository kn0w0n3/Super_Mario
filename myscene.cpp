/*
 * Author: equati0n
 * Date: December 2016
*/

#include "myscene.h"
#include <QKeyEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "player.h"
#include "coin.h"
#include "backgrounditem.h"
#include "castle.h"
#include "goomba.h"
#include "questbox.h"
#include "turtle.h"
#include "piranha.h"
#include "brickplatform.h"
#include "flag.h"
#include "notebox.h"
#include "coincounter.h"
#include "stretch.h"
#include "wallplatform.h"
#include "conveyor.h"
#include "giantgoomba.h"
#include "warptube.h"
#include "stairblock.h"
#include "bomb.h"
#include "redturtle.h"
#include "spiny.h"
#include "score.h"
#include "timer.h"
#include "smallmario.h"
#include "mushroom.h"
#include "gameoverwindow.h"
#include "levelcompletewindow.h"
#include "mushroomquestbox.h"
#include "fireball.h"
#include "firemario.h"

#include "flowerquestbox.h"
#include "flower.h"

MyScene::MyScene(QScrollBar*s , QObject *parent) : QGraphicsScene(0,0,8000,720, parent)
  , m_velocity(7)
  , m_groundLevel(0)
  , m_jumpAnimation(new QPropertyAnimation(this))
  , m_jumpHeight(200)
  , m_fieldWidth(8000)//width of the virtual world
  , m_player()
  , m_smallPlayer()
  , m_sky(0)
  , m_Scene(0)
  , m_coins(0)
  , h_castle()
  , m_goomba()
  , m_questbox(0)
  , m_wallPlatform(0)
  , m_turtle()
  , m_piranha()
  , m_NoteBox(0)
  , m_platform()
  , scroll(s)

{
    initPlayField();

    m_timer.setInterval(20);
    connect(&m_timer, &QTimer::timeout, this, &MyScene::movePlayer);

    mFallTimer.setInterval(20);
    connect(&mFallTimer, &QTimer::timeout, this, &MyScene::fallPlayer);

    m_jumpAnimation->setTargetObject(this);
    m_jumpAnimation->setPropertyName("jumpFactor");
    m_jumpAnimation->setStartValue(0);
    m_jumpAnimation->setKeyValueAt(0.5, 1);
    m_jumpAnimation->setEndValue(0);
    m_jumpAnimation->setDuration(800);
    m_jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this, &MyScene::jumpFactorChanged, this, &MyScene::jumpPlayer);
    connect(m_jumpAnimation, &QPropertyAnimation::stateChanged, this, &MyScene::jumpStatusChanged);

    f_ireMario = false;
    bigMario = false;
    littleMario = true;
    connect(this, SIGNAL(spawnMushroom()),this,SLOT(controlMushroom()));
    connect(this, SIGNAL(spawnFlower()),this,SLOT(controlFlower()));

    jumping = false;
    falling = false;
    m_smallPlayer->addStandingDirection(1);

    soundManager = new SoundManager();
    connect(this, &MyScene::playSound, soundManager, &SoundManager::playSoundEffect);
    emit playSound("level1");
}

void MyScene::setMarioSize(int n){

    int number = n;
    if(number == 0){
        m_smallPlayer = new SmallMario();
        m_smallPlayer->setPos(m_player->pos().x(),m_player->pos().y()+28);
        m_smallPlayer->addDirection(m_player->direction());
        emit playSound("shrink");
        addItem(m_smallPlayer);
        bigMario = false;
        littleMario = true;
        f_ireMario = false;
    }
    else if(number == 1){
        bigMario = false;
        littleMario = false;
        f_ireMario = false;
        emit playSound("stopLevelMusic");
        emit playSound("mario_death");   
        addItem(gameover);
        gameOverWindow = new GameOverWindow();
        gameOverWindow->setFixedSize(557,355);
        gameOverWindow->setWindowFlags(((gameOverWindow->windowFlags()|Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
        gameOverWindow->exec();
    }
    else if(number == 2){
        emit playSound("powerup");
        m_player = new Player();
        m_player->setPos(m_smallPlayer->pos().x(),m_smallPlayer->pos().y()-27);
        m_player->addDirection(m_smallPlayer->direction());
        addItem(m_player);
        bigMario = true;
        f_ireMario = false;
        littleMario = false;
    }
    else if(number == 3){
        emit playSound("powerup");
        bigMario = true;
        f_ireMario = false;
        littleMario = false;
    }
    else if(number == 4){
        emit playSound("powerup");
        fireMario = new FireMario();
        fireMario->setPos(m_player->pos().x(),m_player->pos().y());
        fireMario->addDirection(m_player->direction());
        addItem(fireMario);
        f_ireMario = true;
        bigMario = false;
        littleMario = false;
    }
    else if(number == 5){
        emit playSound("powerup");
        f_ireMario = true;
        bigMario = false;
        littleMario = false;
    }
    else if(number == 6){
        emit playSound("shrink");
        m_smallPlayer = new SmallMario();
        m_smallPlayer->setPos(fireMario->pos().x(),fireMario->pos().y()+28);
        m_smallPlayer->addDirection(fireMario->direction());
        addItem(m_smallPlayer);
        bigMario = false;
        f_ireMario = false;
        littleMario = true;
    }
    else{
        return;
    }
}

//Player key movements
void MyScene::keyPressEvent(QKeyEvent *event){

    if (event->isAutoRepeat())
        return;

    switch (event->key()){
    case Qt::Key_Right:
        if(bigMario){
            m_player->addDirection(1);
            m_player->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(littleMario) {
            m_smallPlayer->addDirection(1);
            m_smallPlayer->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(f_ireMario) {
            fireMario->addDirection(1);
            fireMario->addStandingDirection(1);
            checkTimer();
            break;
        }else{
            break;
        }
        //break;
    case Qt::Key_Left:
        if(bigMario){
            m_player->addDirection(-1);
            m_player->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(littleMario){
            m_smallPlayer->addDirection(-1);
            m_smallPlayer->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(f_ireMario){
            fireMario->addDirection(-1);
            fireMario->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else{
          break;
        }
    case Qt::Key_F:

        if(f_ireMario){

            if((fireMario->direction() == 0) && (fireMario->standingDirection() == -1)){
                fireBall = new FireBall(fireMario->standingDirection());
                fireMario->standShoot();
                fireBall->setPos(fireMario->pos().x()-30,  fireMario->pos().y()+20);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }           
            else if((fireMario->direction() == 0) && (fireMario->standingDirection() != -1)){
                fireBall = new FireBall(1);
                fireMario->standShoot();
                fireBall->setPos(fireMario->pos().x()+45,  fireMario->pos().y()+20);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }         
            else if((fireMario->direction() == 1) && (fireMario->standingDirection() != -1)){
                fireBall = new FireBall(1);
                fireMario->walk();
                fireBall->setPos(fireMario->pos().x()+70, fireMario->pos().y()+17);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }         
            else if((fireMario->direction() == -1) && (fireMario->standingDirection() == -1)){
                fireBall = new FireBall(fireMario->standingDirection());
                fireMario->walk();
                fireBall->setPos(fireMario->pos().x()-70,  fireMario->pos().y()+35);
                addItem(fireBall);
                connect(this->fireBall, SIGNAL(increaseTheScore(int)),this, SLOT(scoreIncrease(int)));
                connect(this->fireBall, SIGNAL(fireballCollision()),this, SLOT(playHitWarp()));
                connect(this->fireBall, SIGNAL(collideGoomba()),this, SLOT(playHitWarp()));
                emit playSound("fireball");
                break;
            }     
        }
        else if(bigMario){

            if((m_player->direction() == 0) && (m_player->standingDirection() == -1)){
                break;
            }
            else if((m_player->direction() == 0) && (m_player->standingDirection() != -1)){
                break;
            }
            else if((m_player->direction() == 1) && (m_player->standingDirection() != -1)){
                break;
            }
            else if((m_player->direction() == -1) && (m_player->standingDirection() == -1)){
                break;
            }
        }
        else if(littleMario){
            if((m_smallPlayer->direction() == 0) && (m_smallPlayer->standingDirection() == -1)){
                break;
            }
            else if((m_smallPlayer->direction() == 0) && (m_smallPlayer->standingDirection() != -1)){
                break;
            }
            else if((m_smallPlayer->direction() == 1) && (m_smallPlayer->standingDirection() != -1)){
                break;
            }
            else if((m_smallPlayer->direction() == -1) && (m_smallPlayer->standingDirection() == -1)){
                break;
            }
        }
        else{
            break;
        }

    case Qt::Key_Space:

        if(bigMario){
            if(mFallTimer.isActive()){
                return;
            }else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                    m_jumpAnimation->start();
                 emit playSound("mario_jump");
                }
            }
            break;
        }
        else if(littleMario){
            if(mFallTimer.isActive()){
                return;
            }
            else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                    m_jumpAnimation->start();
                   emit playSound("mario_jump");
                }
            }
            break;
        }
        else if(f_ireMario){
            if(mFallTimer.isActive()){
                return;
            }else{
                if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
                    m_jumpAnimation->start();
                 emit playSound("mario_jump");
                }
            }
            break;
        }
    default:
        break;
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat())
        return;

    switch (event->key()){
    case Qt::Key_Right:
        if(bigMario){
            m_player->addDirection(-1);
            m_player->addStandingDirection(1);
            checkTimer();
            break;
        }
        else if(littleMario){
            m_smallPlayer->addDirection(-1);
            checkTimer();
            break;
        }
        else if(f_ireMario){
            fireMario->addDirection(-1);
            fireMario->addStandingDirection(1);
            checkTimer();
            break;
        }

    case Qt::Key_Left:
        if(bigMario){
            m_player->addDirection(1);
            m_player->addStandingDirection(-1);
            checkTimer();
            break;
        }
        else if(littleMario){
            m_smallPlayer->addDirection(1);
            checkTimer();
            break;
        }
        else if(f_ireMario){
            fireMario->addDirection(1);
            fireMario->addStandingDirection(-1);
            checkTimer();
            break;
        }
    default:
        break;
    }
}

void MyScene::movePlayer(){

    checkCollidingCoin();
    checkCollidingMushroomQuestBox();
    checkCollidingFlowerQuestBox();
    checkCollidingQuestBox();
    checkCollidingStairBlock();
    checkCollidingFlag();
    checkCollidingWarpTube();
    if(bigMario){
        if(m_player->isFalling()){
            return;
        }
    }
    else if(littleMario){
        if(m_smallPlayer->isFalling()){
            return;
        }
    }
    else if(f_ireMario){
        if(fireMario->isFalling()){
            return;
        }
    }

    if(bigMario){
        m_player->nextFrame();
    }
    else if(littleMario){

        m_smallPlayer->nextFrame();
    }
    else if(f_ireMario){

        fireMario->nextFrame();
    }

    if(bigMario){
        int direction = m_player->direction();
        if (0 == direction)
            return;
    }
    else if(littleMario){
        int direction = m_smallPlayer->direction();
        if (0 == direction)
            return;
    }
    else if(f_ireMario){
        int direction = fireMario->direction();
        if (0 == direction)
            return;
    }

    if(bigMario){   
        if(!(m_platform && m_player->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
            if(m_platform){
                m_player->fall();
                mFallTimer.start();              
            }
        }
    }
    else if(littleMario){
        if(!(m_platform && m_smallPlayer->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
            if(m_platform){
                m_smallPlayer->fall();
                mFallTimer.start();
            }
        }
    }
    else if(f_ireMario){
        if(!(m_platform && fireMario->isTouchingPlatform(m_platform))&& m_jumpAnimation->state() == QAbstractAnimation::Stopped){
            if(m_platform){
                fireMario->fall();
                mFallTimer.start();
            }
        }
    }
    else{
        return;
    }

    if(bigMario){

        int direction = m_player->direction();
        const int dx = direction * m_velocity;

        if (direction > 0){

            if(m_player->pos().x()==7956){
                return;
            }

            m_player->moveBy(dx, 0);
            int diff = m_player->pos().x() - scroll->value();

            if(diff > 800){

                if(scroll->value() > 6720){
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0){

            if(m_player->pos().x()<0){
                return;
            }

            m_player->moveBy(dx, 0);
            int diff = m_player->pos().x() - scroll->value();

            if(diff < 600){

                if(m_sky->pos().x() == 0){
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }
    else if (littleMario){

        int direction = m_smallPlayer->direction();
        const int dx = direction * m_velocity;

        if (direction > 0){

            if(m_smallPlayer->pos().x()==7956){
                return;
            }

            m_smallPlayer->moveBy(dx, 0);
            int diff2 = m_smallPlayer->pos().x() - scroll->value();

            if(diff2 > 800){

                if(scroll->value() > 6720){
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0){

            if(m_smallPlayer->pos().x()<0){
                return;
            }

            m_smallPlayer->moveBy(dx, 0);
            int diff2 = m_smallPlayer->pos().x() - scroll->value();

            if(diff2 < 600){

                if(m_sky->pos().x() == 0){
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }

    else if (f_ireMario){
        int direction = fireMario->direction();
        const int dx = direction * m_velocity;
        if (direction > 0){

            if(fireMario->pos().x()==7956){
                return;
            }

            fireMario->moveBy(dx, 0);
            int diff2 = fireMario->pos().x() - scroll->value();

            if(diff2 > 800){

                if(scroll->value() > 6720){
                    qDebug()<<"6720";
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }

        if (direction < 0){

            if(fireMario->pos().x()<0){
                return;
            }

            fireMario->moveBy(dx, 0);
            int diff2 = fireMario->pos().x() - scroll->value();

            if(diff2 < 600){

                if(m_sky->pos().x() == 0){
                    return;
                }

                scroll->setValue(dx + scroll->value());
                m_sky->setPos(dx + m_sky->pos().x(), 0);
                m_Scene->setPos(dx + m_Scene->pos().x(), m_Scene->y());
                m_countLogo->setPos(dx + m_countLogo->pos().x(), m_countLogo->y());
                m_count->setPos(dx + m_count->pos().x(), m_count->y());
                m_score->setPos(dx + m_score->pos().x(), m_score->y());
                m_gameTimer->setPos(dx + m_gameTimer->pos().x(), m_gameTimer->y());
                m_scoreLogo->setPos(dx + m_scoreLogo->pos().x(), m_scoreLogo->y());
                m_timerLogo->setPos(dx + m_timerLogo->pos().x(), m_timerLogo->y());
                gameover->setPos(dx + gameover->pos().x(), gameover->y());
                courseclear->setPos(dx + courseclear->pos().x(), courseclear->y());
            }
        }
    }

    else{
        return;
    }
}

void MyScene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState){
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
        //handleCollisionWithPlatform();
    }
}

//Make Mario detect other platform when falling
void MyScene::fallPlayer(){

    if(bigMario){
        m_player->setPos(m_player->pos().x(), m_player->pos().y() +30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform()){
            mFallTimer.stop();
            m_player->walk();
        }
        else if(m_player->pos().y() + m_player->boundingRect().height() >= m_groundLevel){
            m_player->setPos(m_player->pos().x(), m_groundLevel - m_player->boundingRect().height());
            mFallTimer.stop();
            m_player->walk();
            m_platform = 0;
        }
    }
    else if(littleMario){
        m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_smallPlayer->pos().y() +30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform()){
            mFallTimer.stop();
            m_smallPlayer->walk();

        } else if(m_smallPlayer->pos().y() + m_smallPlayer->boundingRect().height() >= m_groundLevel){
            m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_groundLevel - m_smallPlayer->boundingRect().height());
            mFallTimer.stop();
            m_smallPlayer->walk();
            m_platform = 0;
        }
    }
    else if(f_ireMario){
        fireMario->setPos(fireMario->pos().x(), fireMario->pos().y()+30);
        QGraphicsItem* item = collidingPlatforms();
        if(item && handleCollisionWithPlatform()){
            mFallTimer.stop();
            fireMario->walk();

        } else if(fireMario->pos().y() + fireMario->boundingRect().height() >= m_groundLevel){
            fireMario->setPos(fireMario->pos().x(), m_groundLevel - fireMario->boundingRect().height());
            mFallTimer.stop();
            fireMario->walk();
            m_platform = 0;
        }
    }
}

//Player jump movement
void MyScene::jumpPlayer(){

    checkCollidingCoin();
    checkCollidingMushroomQuestBox();
    checkCollidingFlowerQuestBox();
    checkCollidingQuestBox();
    checkCollidingStairBlock();
    checkCollidingFlag();
    checkCollidingWarpTube();

    if (QAbstractAnimation::Stopped == m_jumpAnimation->state()){
        m_player->stand();
        return;
    }

    if(bigMario){
        QGraphicsItem* item = collidingPlatforms();
        if(item){
            if(m_player->isTouchingHead(item)){

                m_jumpAnimation->stop();

                if(m_platform){
                    m_player->setPos(m_player->pos().x(), m_platform->pos().y() - m_player->boundingRect().height());
                    return;
                }
                if(!m_platform){
                    m_player->setPos(m_player->pos().x(), m_groundLevel - m_player->boundingRect().height());
                    return;
                }
            }
            else{
                if(handleCollisionWithPlatform()){
                    return;
                }
            }
        }
    }
    else if(littleMario){
        QGraphicsItem* item = collidingPlatforms();
        if(item){
            if(m_smallPlayer->isTouchingHead(item)){

                m_jumpAnimation->stop();

                if(m_platform){
                    m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_platform->pos().y() - m_smallPlayer->boundingRect().height());
                    return;
                }
                if(!m_platform){
                    m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_groundLevel - m_smallPlayer->boundingRect().height());
                    return;
                }
            }
            else{
                if(handleCollisionWithPlatform()){
                    return;
                }
            }
        }
    }
    else if(f_ireMario){
        QGraphicsItem* item = collidingPlatforms();
        if(item){
            if(fireMario->isTouchingHead(item)){

                m_jumpAnimation->stop();

                if(m_platform){
                    fireMario->setPos(fireMario->pos().x(), m_platform->pos().y() - fireMario->boundingRect().height());
                    return;
                }
                if(!m_platform){
                    fireMario->setPos(fireMario->pos().x(), m_groundLevel - fireMario->boundingRect().height());
                    return;
                }
            }
            else{
                if(handleCollisionWithPlatform()){
                    return;
                }
            }
        }
    }

    if(bigMario){
        if(mFallTimer.isActive()){
            return;
        }
        qreal y = (m_groundLevel - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(m_platform){
            y = (m_platform->pos().y() - m_player->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
            if(!(m_platform && m_player->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
                if((m_player->pos().x() < m_platform->pos().x()) || (m_player->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width())){
                    if(!m_platform){
                        m_platform = 0;
                    }
                    if(m_player->pos().y() < m_groundLevel){
                        m_player->fall();
                        mFallTimer.start();
                        return;
                    }
                }
            }
        }
        m_player->setPos(m_player->pos().x(), y);
    }
    else if(littleMario){
        if(mFallTimer.isActive()){
            return;
        }
        qreal p = (m_groundLevel - m_smallPlayer->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(m_platform){
            p = (m_platform->pos().y() - m_smallPlayer->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
            if(!(m_platform && m_smallPlayer->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
                if(m_smallPlayer->pos().x() < m_platform->pos().x() || m_smallPlayer->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width()){
                    if(!m_platform){
                        m_platform = 0;
                    }
                    if(m_smallPlayer->pos().y() < m_groundLevel){
                        m_smallPlayer->fall();
                        mFallTimer.start();
                        return;
                    }
                }
            }
        }
        m_smallPlayer->setPos(m_smallPlayer->pos().x(), p);
    }
    else if(f_ireMario){
        if(mFallTimer.isActive()){
            return;
        }
        qreal y2 = (m_groundLevel - fireMario->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
        if(m_platform){
            y2 = (m_platform->pos().y() - fireMario->boundingRect().height()) - m_jumpAnimation->currentValue().toReal() * m_jumpHeight;
            if(!(m_platform && fireMario->isTouchingPlatform(m_platform)) && m_jumpFactor < 0.1 ) {
                if((fireMario->pos().x() < m_platform->pos().x()) || (fireMario->pos().x() > m_platform->pos().x() + m_platform->boundingRect().width())){
                    if(!m_platform){
                        m_platform = 0;
                    }
                    if(fireMario->pos().y() < m_groundLevel){
                        fireMario->fall();
                        mFallTimer.start();
                        return;
                    }
                }
            }
        }
        fireMario->setPos(fireMario->pos().x(), y2);
    }
}

//Creating the scene and adding items
void MyScene::initPlayField(){

    setSceneRect(0,0,8000,720);

    m_groundLevel = 660;

    //add sky
    m_sky = new BackgroundItem(QPixmap(":images/sky"));
    m_sky->setPos(0,0);
    addItem(m_sky);

    //Game over screen
    gameover = new BackgroundItem(QPixmap(":images/gameovers"));

    //Course clear screen
    courseclear = new BackgroundItem(QPixmap(":images/c2"));

    //add ground
    m_ground = new BackgroundItem(QPixmap(":images/ground"));
    addItem(m_ground);
    m_ground->setPos(0, m_groundLevel );

    //add scene image
    m_Scene = new BackgroundItem(QPixmap(":images/Scene"));
    m_Scene->setPos(0, m_groundLevel - m_Scene->boundingRect().height());
    addItem(m_Scene);

    //Image for counter
    m_countLogo = new BackgroundItem(QPixmap(":images/count"));
    m_countLogo->setPos(30, m_groundLevel -652 );
    addItem(m_countLogo);

    //Add Score Text
    m_scoreLogo = new BackgroundItem(QPixmap(":images/scoretext"));
    m_scoreLogo->setPos(900, m_groundLevel -647 );
    addItem(m_scoreLogo);

    //Image for game timer
    m_timerLogo = new BackgroundItem(QPixmap(":images/clock"));
    m_timerLogo->setPos(1100, m_groundLevel -654 );
    addItem(m_timerLogo);

    //Add wall structures
    m_wall2 = new BackgroundItem(QPixmap(":images/wallg.png"));
    m_wall2->setPos(3100, m_groundLevel - m_wall2->boundingRect().height());
    addItem(m_wall2);

    m_wall = new BackgroundItem(QPixmap(":images/wallf2.png"));
    m_wall->setPos(2900, m_groundLevel - m_wall->boundingRect().height());
    addItem(m_wall);

    m_wall3 = new BackgroundItem(QPixmap(":images/walli.png"));
    m_wall3->setPos(3350, m_groundLevel - m_wall3->boundingRect().height());
    addItem(m_wall3);

    //Add flag Pole
    m_flag = new BackgroundItem(QPixmap(":images/flag"));
    m_flag->setPos(7234, m_groundLevel - m_flag->boundingRect().height());
    addItem(m_flag);

    //Add Castle
    m_castle = new BackgroundItem(QPixmap(":images/castle"));
    m_castle->setPos(7637, m_groundLevel - m_castle->boundingRect().height());
    addItem(m_castle);

    //Add Coins
    m_coins = new Coin();
    m_coins->setPos(1300, m_groundLevel - m_coins->boundingRect().height()-200);
    addItem(m_coins);
    startTimer( 100 );

    m_coins2 = new Coin();
    m_coins2->setPos(1300, m_groundLevel - m_coins2->boundingRect().height()-250);
    addItem(m_coins2);

    m_coins3 = new Coin();
    m_coins3->setPos(1300, m_groundLevel - m_coins3->boundingRect().height()-300);
    addItem(m_coins3);

    m_coins4 = new Coin();
    m_coins4->setPos(1300, m_groundLevel - m_coins4->boundingRect().height()-350);
    addItem(m_coins4);

    m_coins5 = new Coin();
    m_coins5->setPos(1350, m_groundLevel - m_coins5->boundingRect().height()-350);
    addItem(m_coins5);

    m_coins6 = new Coin();
    m_coins6->setPos(1400, m_groundLevel - m_coins6->boundingRect().height()-350);
    addItem(m_coins6);

    m_coins7 = new Coin();
    m_coins7->setPos(1400, m_groundLevel - m_coins7->boundingRect().height()-300);
    addItem(m_coins7);

    m_coins8 = new Coin();
    m_coins8->setPos(1350, m_groundLevel - m_coins8->boundingRect().height()-250);
    addItem(m_coins8);

    m_coins9 = new Coin();
    m_coins9->setPos(1400, m_groundLevel - m_coins9->boundingRect().height()-200);
    addItem(m_coins9);

    m_coins10 = new Coin();
    m_coins10->setPos(1500, m_groundLevel - m_coins10->boundingRect().height()-200);
    addItem(m_coins10);

    m_coins11 = new Coin();
    m_coins11->setPos(1500, m_groundLevel - m_coins11->boundingRect().height()-250);
    addItem(m_coins11);

    m_coins12 = new Coin();
    m_coins12->setPos(1500, m_groundLevel - m_coins12->boundingRect().height()-300);
    addItem(m_coins12);

    m_coins13 = new Coin();
    m_coins13->setPos(1500, m_groundLevel - m_coins13->boundingRect().height()-350);
    addItem(m_coins13);

    m_coins14 = new Coin();
    m_coins14->setPos(1550, m_groundLevel -  m_coins14->boundingRect().height()-350);
    addItem( m_coins14);

    m_coins15 = new Coin();
    m_coins15->setPos(1600, m_groundLevel - m_coins15->boundingRect().height()-350);
    addItem(m_coins15);

    m_coins16 = new Coin();
    m_coins16->setPos(1500, m_groundLevel - m_coins16->boundingRect().height()-200);
    addItem(m_coins16);

    m_coins17 = new Coin();
    m_coins17->setPos(1550, m_groundLevel - m_coins17->boundingRect().height()-200);
    addItem(m_coins17);

    m_coins18 = new Coin();
    m_coins18->setPos(1600, m_groundLevel - m_coins18->boundingRect().height()-200);
    addItem(m_coins18);

    m_coins19 = new Coin();
    m_coins19->setPos(1700, m_groundLevel - m_coins19->boundingRect().height()-200);
    addItem(m_coins19);

    m_coins20 = new Coin();
    m_coins20->setPos(1700, m_groundLevel - m_coins20->boundingRect().height()-250);
    addItem(m_coins20);

    m_coins21 = new Coin();
    m_coins21->setPos(1700, m_groundLevel - m_coins21->boundingRect().height()-300);
    addItem(m_coins21);

    m_coins22 = new Coin();
    m_coins22->setPos(1700, m_groundLevel - m_coins22->boundingRect().height()-350);
    addItem(m_coins22);

    m_coins23 = new Coin();
    m_coins23->setPos(1750, m_groundLevel - m_coins23->boundingRect().height()-350);
    addItem(m_coins23);

    m_coins24 = new Coin();
    m_coins24->setPos(1800, m_groundLevel - m_coins24->boundingRect().height()-350);
    addItem(m_coins24);

    m_coins25 = new Coin();
    m_coins25->setPos(1750, m_groundLevel - m_coins25->boundingRect().height()-200);
    addItem(m_coins25);

    m_coins26 = new Coin();
    m_coins26->setPos(1800, m_groundLevel - m_coins26->boundingRect().height()-200);
    addItem(m_coins26);

    //first wall structure coins
    m_coins27 = new Coin();
    m_coins27->setPos(2970, m_groundLevel - m_coins27->boundingRect().height()-290);
    addItem(m_coins27);

    m_coins28 = new Coin();
    m_coins28->setPos(3020, m_groundLevel - m_coins28->boundingRect().height()-290);
    addItem(m_coins28);

    m_coins29 = new Coin();
    m_coins29->setPos(3070, m_groundLevel - m_coins29->boundingRect().height()-290);
    addItem(m_coins29);

    m_coins30 = new Coin();
    m_coins30->setPos(2920, m_groundLevel - m_coins30->boundingRect().height()-290);
    addItem(m_coins30);

    //Bottom wall structure coins
    m_coins32 = new Coin();
    m_coins32->setPos(4110, m_groundLevel - m_coins32->boundingRect().height()-150);
    addItem(m_coins32);

    m_coins33 = new Coin();
    m_coins33->setPos(3360, m_groundLevel - m_coins33->boundingRect().height()-150);
    addItem(m_coins33);

    m_coins34 = new Coin();
    m_coins34->setPos(3410, m_groundLevel - m_coins34->boundingRect().height()-150);
    addItem(m_coins34);

    m_coins35 = new Coin();
    m_coins35->setPos(3460, m_groundLevel - m_coins35->boundingRect().height()-150);
    addItem(m_coins35);

    m_coins36 = new Coin();
    m_coins36->setPos(3510, m_groundLevel - m_coins36->boundingRect().height()-150);
    addItem(m_coins36);

    m_coins37 = new Coin();
    m_coins37->setPos(3560, m_groundLevel - m_coins37->boundingRect().height()-150);
    addItem(m_coins37);

    m_coins38 = new Coin();
    m_coins38->setPos(3610, m_groundLevel - m_coins38->boundingRect().height()-150);
    addItem(m_coins38);

    m_coins39 = new Coin();
    m_coins39->setPos(3660, m_groundLevel - m_coins39->boundingRect().height()-150);
    addItem(m_coins39);

    m_coins40 = new Coin();
    m_coins40->setPos(3710, m_groundLevel - m_coins40->boundingRect().height()-150);
    addItem(m_coins40);

    m_coins41 = new Coin();
    m_coins41->setPos(3760, m_groundLevel - m_coins41->boundingRect().height()-150);
    addItem(m_coins41);

    m_coins42 = new Coin();
    m_coins42->setPos(3810, m_groundLevel - m_coins42->boundingRect().height()-150);
    addItem(m_coins42);

    m_coins43 = new Coin();
    m_coins43->setPos(3860, m_groundLevel - m_coins43->boundingRect().height()-150);
    addItem(m_coins43);

    m_coins44 = new Coin();
    m_coins44->setPos(3910, m_groundLevel - m_coins44->boundingRect().height()-150);
    addItem(m_coins44);

    m_coins45 = new Coin();
    m_coins45->setPos(3960, m_groundLevel - m_coins45->boundingRect().height()-150);
    addItem(m_coins45);

    m_coins46 = new Coin();
    m_coins46->setPos(4010, m_groundLevel - m_coins46->boundingRect().height()-150);
    addItem(m_coins46);

    m_coins47 = new Coin();
    m_coins47->setPos(4060, m_groundLevel - m_coins47->boundingRect().height()-150);
    addItem(m_coins47);

    //Notebox coins
    m_coins48 = new Coin();
    m_coins48->setPos(3995, m_groundLevel - m_coins48->boundingRect().height()-370);
    addItem(m_coins48);

    m_coins49 = new Coin();
    m_coins49->setPos(4030, m_groundLevel - m_coins49->boundingRect().height()-440);
    addItem(m_coins49);

    m_coins50 = new Coin();
    m_coins50->setPos(4108, m_groundLevel - m_coins50->boundingRect().height()-495);
    addItem(m_coins50);

    m_coins51 = new Coin();
    m_coins51->setPos(4190, m_groundLevel - m_coins51->boundingRect().height()-450);
    addItem(m_coins51);

    m_coins52 = new Coin();
    m_coins52->setPos(4240, m_groundLevel - m_coins52->boundingRect().height()-390);
    addItem(m_coins52);

    m_coins53 = new Coin();
    m_coins53->setPos(4290, m_groundLevel - m_coins53->boundingRect().height()-465);
    addItem(m_coins53);

    m_coins54 = new Coin();
    m_coins54->setPos(4360, m_groundLevel - m_coins54->boundingRect().height()-520);
    addItem(m_coins54);

    m_coins55 = new Coin();
    m_coins55->setPos(4435, m_groundLevel - m_coins55->boundingRect().height()-465);
    addItem(m_coins55);

    m_coins56 = new Coin();
    m_coins56->setPos(4490, m_groundLevel - m_coins56->boundingRect().height()-410);
    addItem(m_coins56);

    m_coins57 = new Coin();
    m_coins57->setPos(4540, m_groundLevel - m_coins57->boundingRect().height()-490);
    addItem(m_coins57);

    m_coins58 = new Coin();
    m_coins58->setPos(4610, m_groundLevel - m_coins58->boundingRect().height()-540);
    addItem(m_coins58);

    m_coins59 = new Coin();
    m_coins59->setPos(4680, m_groundLevel - m_coins59->boundingRect().height()-500);
    addItem(m_coins59);

    m_coins60 = new Coin();
    m_coins60->setPos(4730, m_groundLevel - m_coins60->boundingRect().height()-440);
    addItem(m_coins60);

    m_coins61 = new Coin();
    m_coins61->setPos(650, m_groundLevel - m_coins61->boundingRect().height()-280);
    addItem(m_coins61);

    m_coins62 = new Coin();
    m_coins62->setPos(2100, m_groundLevel - m_coins62->boundingRect().height()-250);
    addItem(m_coins62);

    m_coins63 = new Coin();
    m_coins63->setPos(815, m_groundLevel - m_coins63->boundingRect().height()-320);
    addItem(m_coins63);

    m_coins64 = new Coin();
    m_coins64->setPos(2155, m_groundLevel - m_coins64->boundingRect().height()-250);
    addItem(m_coins64);

    m_coins65 = new Coin();
    m_coins65->setPos(2210, m_groundLevel - m_coins65->boundingRect().height()-250);
    addItem(m_coins65);

    m_coins66 = new Coin();
    m_coins66->setPos(2265, m_groundLevel - m_coins66->boundingRect().height()-250);
    addItem(m_coins66);

    m_coins67 = new Coin();
    m_coins67->setPos(2320, m_groundLevel - m_coins67->boundingRect().height()-250);
    addItem(m_coins67);

    m_coins68 = new Coin();
    m_coins68->setPos(2375, m_groundLevel - m_coins68->boundingRect().height()-250);
    addItem(m_coins68);

    //End Level coins
    m_coins69 = new Coin();
    m_coins69->setPos(5400, m_groundLevel - m_coins69->boundingRect().height()-250);
    addItem(m_coins69);

    m_coins70 = new Coin();
    m_coins70->setPos(5400, m_groundLevel - m_coins70->boundingRect().height()-300);
    addItem(m_coins70);

    m_coins71 = new Coin();
    m_coins71->setPos(5400, m_groundLevel - m_coins71->boundingRect().height()-350);
    addItem(m_coins71);

    m_coins72 = new Coin();
    m_coins72->setPos(5350, m_groundLevel - m_coins72->boundingRect().height()-250);
    addItem(m_coins72);

    m_coins73 = new Coin();
    m_coins73->setPos(5350, m_groundLevel - m_coins73->boundingRect().height()-300);
    addItem(m_coins73);

    m_coins74 = new Coin();
    m_coins74->setPos(5350, m_groundLevel - m_coins74->boundingRect().height()-350);
    addItem(m_coins74);

    m_coins75 = new Coin();
    m_coins75->setPos(5300, m_groundLevel - m_coins75->boundingRect().height()-250);
    addItem(m_coins75);

    m_coins76 = new Coin();
    m_coins76->setPos(5300, m_groundLevel - m_coins76->boundingRect().height()-300);
    addItem(m_coins76);

    m_coins77 = new Coin();
    m_coins77->setPos(5300, m_groundLevel - m_coins77->boundingRect().height()-350);
    addItem(m_coins77);

    m_coins78 = new Coin();
    m_coins78->setPos(5250, m_groundLevel - m_coins78->boundingRect().height()-250);
    addItem(m_coins78);

    m_coins79 = new Coin();
    m_coins79->setPos(5250, m_groundLevel - m_coins79->boundingRect().height()-300);
    addItem(m_coins79);

    m_coins80 = new Coin();
    m_coins80->setPos(5250, m_groundLevel - m_coins80->boundingRect().height()-350);
    addItem(m_coins80);

    m_coins81 = new Coin();
    m_coins81->setPos(5200, m_groundLevel - m_coins81->boundingRect().height()-250);
    addItem(m_coins81);

    m_coins82 = new Coin();
    m_coins82->setPos(5200, m_groundLevel - m_coins82->boundingRect().height()-300);
    addItem(m_coins82);

    m_coins83 = new Coin();
    m_coins83->setPos(5200, m_groundLevel - m_coins83->boundingRect().height()-350);
    addItem(m_coins83);

    m_coins84 = new Coin();
    m_coins84->setPos(5150, m_groundLevel - m_coins84->boundingRect().height()-250);
    addItem(m_coins84);

    m_coins85 = new Coin();
    m_coins85->setPos(5150, m_groundLevel - m_coins85->boundingRect().height()-300);
    addItem(m_coins85);

    m_coins86 = new Coin();
    m_coins86->setPos(5150, m_groundLevel - m_coins86->boundingRect().height()-350);
    addItem(m_coins86);

    m_coins87 = new Coin();
    m_coins87->setPos(5700, m_groundLevel - m_coins87->boundingRect().height()-350);
    addItem(m_coins87);

    m_coins88 = new Coin();
    m_coins88->setPos(5750, m_groundLevel - m_coins88->boundingRect().height()-350);
    addItem(m_coins88);

    m_coins89 = new Coin();
    m_coins89->setPos(5800, m_groundLevel - m_coins89->boundingRect().height()-350);
    addItem(m_coins89);

    m_coins90 = new Coin();
    m_coins90->setPos(5850, m_groundLevel - m_coins90->boundingRect().height()-350);
    addItem(m_coins90);

    m_coins91 = new Coin();
    m_coins91->setPos(5900, m_groundLevel - m_coins91->boundingRect().height()-350);
    addItem(m_coins91);

    m_coins92 = new Coin();
    m_coins92->setPos(5950, m_groundLevel - m_coins92->boundingRect().height()-350);
    addItem(m_coins92);

    m_coins93 = new Coin();
    m_coins93->setPos(6000, m_groundLevel - m_coins93->boundingRect().height()-350);
    addItem(m_coins93);

    m_coins94 = new Coin();
    m_coins94->setPos(6050, m_groundLevel - m_coins94->boundingRect().height()-350);
    addItem(m_coins94);

    m_coins95 = new Coin();
    m_coins95->setPos(6100, m_groundLevel - m_coins95->boundingRect().height()-350);
    //addItem(m_coins95);

    m_coins96 = new Coin();
    m_coins96->setPos(6140, m_groundLevel - m_coins96->boundingRect().height()-350);
    addItem(m_coins96);

    m_coins97 = new Coin();
    m_coins97->setPos(6105, m_groundLevel - m_coins97->boundingRect().height()-300);
    addItem(m_coins97);

    m_coins98 = new Coin();
    m_coins98->setPos(6060, m_groundLevel - m_coins98->boundingRect().height()-250);
    addItem(m_coins98);

    m_coins99 = new Coin();
    m_coins99->setPos(6105, m_groundLevel - m_coins99->boundingRect().height()-400);
    addItem(m_coins99);

    m_coins100 = new Coin();
    m_coins100->setPos(6060, m_groundLevel - m_coins100->boundingRect().height()-450);
    addItem(m_coins100);

    //Add Questionbox
    m_questbox = new QuestBox(1);
    m_questbox->setPos(643, m_groundLevel - m_questbox->boundingRect().height()-100);
    addItem(m_questbox);

    m_questbox2 = new QuestBox(1);
    m_questbox2->setPos(2755, m_groundLevel - m_questbox2->boundingRect().height()-150);
    addItem(m_questbox2);

    m_questbox3 = new QuestBox(1);
    m_questbox3->setPos(2658, m_groundLevel - m_questbox3->boundingRect().height()-100);
    addItem(m_questbox3);

    //Wall scructure questbox
    m_questbox4 = new QuestBox(1);
    m_questbox4->setPos(3250, m_groundLevel - m_questbox4->boundingRect().height()-450);
    addItem(m_questbox4);

    m_questbox5 = new QuestBox(1);
    m_questbox5->setPos(3750, m_groundLevel - m_questbox5->boundingRect().height()-250);
    addItem(m_questbox5);

    //Rcc Coin area Questbox
    m_questbox6 = new QuestBox(1);
    m_questbox6->setPos(1745, m_groundLevel - m_questbox6->boundingRect().height()-130);
    addItem(m_questbox6);

    m_questbox7 = new QuestBox(1);
    m_questbox7->setPos(1545, m_groundLevel - m_questbox7->boundingRect().height()-130);
    addItem(m_questbox7);

    m_questbox8 = new QuestBox(1);
    m_questbox8->setPos(1345, m_groundLevel - m_questbox8->boundingRect().height()-130);
    addItem(m_questbox8);

    m_questbox9 = new QuestBox(1);
    m_questbox9->setPos(6240, m_groundLevel - m_questbox9->boundingRect().height()-350);
    addItem(m_questbox9);

    m_questbox10 = new QuestBox(1);
    m_questbox10->setPos(5600, m_groundLevel - m_questbox10->boundingRect().height()-350);
    addItem(m_questbox10);

    m_questbox11 = new QuestBox(1);
    m_questbox11->setPos(5153, m_groundLevel - m_questbox11->boundingRect().height()-200);
    addItem(m_questbox11);

    m_questbox12 = new QuestBox(1);
    m_questbox12->setPos(7200, m_groundLevel - m_questbox11->boundingRect().height()-100);
    addItem(m_questbox12);

    mushroomQuestBox = new MushroomQuestBox(1);
    mushroomQuestBox->setPos(200, m_groundLevel - mushroomQuestBox->boundingRect().height()-100);
    mushroomQuestBox->setZValue(1);
    addItem(mushroomQuestBox);

    flowerQuestBox = new FlowerQuestBox(1);
    flowerQuestBox->setPos(1085, m_groundLevel - flowerQuestBox->boundingRect().height()-250);
    flowerQuestBox->setZValue(3);
    addItem(flowerQuestBox);

    //Add brick platforms
    mBrickPlatform = new BrickPlatform(5);
    mBrickPlatform->setPos(404, m_groundLevel - mBrickPlatform->boundingRect().height()-100);
    addItem(mBrickPlatform);

    mBrickPlatform2 = new BrickPlatform(1);
    mBrickPlatform2->setPos(648, m_groundLevel - mBrickPlatform2->boundingRect().height()-225);
    addItem(mBrickPlatform2);

    mBrickPlatform3 = new BrickPlatform(1);
    mBrickPlatform3->setPos(810, m_groundLevel - mBrickPlatform3->boundingRect().height()-270);
    addItem(mBrickPlatform3);

    mBrickPlatform4 = new BrickPlatform(5);
    mBrickPlatform4->setPos(1000, m_groundLevel - mBrickPlatform4->boundingRect().height()-100);
    addItem(mBrickPlatform4);

    mBrickPlatform5 = new BrickPlatform(5);
    mBrickPlatform5->setPos(5500, m_groundLevel - mBrickPlatform5->boundingRect().height()-150);
    addItem(mBrickPlatform5);

    mBrickPlatform6 = new BrickPlatform(5);
    mBrickPlatform6->setPos(5200, m_groundLevel - mBrickPlatform6->boundingRect().height()-200);
    addItem(mBrickPlatform6);

    mBrickPlatform7 = new BrickPlatform(1);
    mBrickPlatform7->setPos(5900, m_groundLevel - mBrickPlatform7->boundingRect().height()-150);
    addItem(mBrickPlatform7);

    mBrickPlatform8 = new BrickPlatform(7);
    mBrickPlatform8->setPos(6100, m_groundLevel - mBrickPlatform8->boundingRect().height()-150);
    addItem(mBrickPlatform8);

    //Add wall platform
    m_wallPlatform = new WallPlatform(6);
    m_wallPlatform->setPos(2910, m_groundLevel - m_wallPlatform->boundingRect().height()-240);
    addItem(m_wallPlatform);

    m_wallPlatform2  = new WallPlatform(8);
    m_wallPlatform2->setPos(3115, m_groundLevel - m_wallPlatform2->boundingRect().height()-300);
    addItem(m_wallPlatform2);

    m_wallPlatform3 = new WallPlatform(16);
    m_wallPlatform3->setPos(3370, m_groundLevel - m_wallPlatform3->boundingRect().height()-103);
    addItem(m_wallPlatform3);

    m_wallPlatform4 = new WallPlatform(20);
    m_wallPlatform4->setPos(5000, m_groundLevel );
    addItem(m_wallPlatform4);

    m_wallPlatform5 = new WallPlatform(10);
    m_wallPlatform5->setPos(1345, m_groundLevel );
    addItem(m_wallPlatform5);

    m_wallPlatform6 = new WallPlatform(3);
    m_wallPlatform6->setPos(404, m_groundLevel );
    addItem(m_wallPlatform6);

    m_wallPlatform7 = new WallPlatform(3);
    m_wallPlatform7->setPos(1000, m_groundLevel );
    addItem(m_wallPlatform7);

    m_wallPlatform8 = new WallPlatform(4);
    m_wallPlatform8->setPos(3115, m_groundLevel );
    addItem(m_wallPlatform8);

    m_wallPlatform9 = new WallPlatform(3);
    m_wallPlatform9->setPos(4960, m_groundLevel );
    addItem(m_wallPlatform9);

    m_wallPlatform10 = new WallPlatform(3);
    m_wallPlatform10->setPos(6100, m_groundLevel );
    addItem(m_wallPlatform10);

    m_wallPlatform11 = new WallPlatform(3);
    m_wallPlatform11->setPos(2100, m_groundLevel- m_wallPlatform11->boundingRect().height()-150 );
    addItem(m_wallPlatform11);

    //Add Notebox
    m_NoteBox = new NoteBox(5);
    m_NoteBox->setPos(2100, m_groundLevel - m_NoteBox->boundingRect().height()-130);
    addItem(m_NoteBox);

    m_NoteBox2 = new NoteBox(1);
    m_NoteBox2->setPos(3980, m_groundLevel - m_NoteBox2->boundingRect().height()-300);
    addItem(m_NoteBox2);

    m_NoteBox3 = new NoteBox(1);
    m_NoteBox3->setPos(4230, m_groundLevel - m_NoteBox3->boundingRect().height()-325);
    addItem(m_NoteBox3);

    m_NoteBox4 = new NoteBox(1);
    m_NoteBox4->setPos(4480, m_groundLevel - m_NoteBox4->boundingRect().height()-340);
    addItem(m_NoteBox4);

    m_NoteBox5 = new NoteBox(1);
    m_NoteBox5->setPos(4720, m_groundLevel - m_NoteBox5->boundingRect().height()-365);
    addItem(m_NoteBox5);

    m_NoteBox6 = new NoteBox(5);
    m_NoteBox6->setPos(4940, m_groundLevel - m_NoteBox6->boundingRect().height()-400);
    addItem(m_NoteBox6);

    //Add Goomba
    m_goomba = new Goomba(QRectF(m_wallPlatform6 ->pos(), m_wallPlatform6 ->boundingRect().size()), -1);
    m_goomba->setPos(400, m_groundLevel - m_goomba->boundingRect().height()-150);
    addItem(m_goomba);
    connect(this->m_goomba, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add Turtle
    m_turtle = new Turtle(QRectF(m_wallPlatform7->pos(), m_wallPlatform7->boundingRect().size()), -1);
    m_turtle->setPos(995, m_groundLevel - m_turtle->boundingRect().height()-150);
    addItem(m_turtle);
    connect(this->m_turtle, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    m_turtle2 = new Turtle(QRectF(m_wallPlatform8->pos(), m_wallPlatform8->boundingRect().size()), -1);
    m_turtle2->setPos(3250, m_groundLevel - m_turtle2->boundingRect().height()-345);
    addItem(m_turtle2);
    connect(this->m_turtle2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add piranha plant
    m_piranha = new Piranha();
    m_piranha->setPos(773, m_groundLevel - m_piranha->boundingRect().height()-95);
    addItem(m_piranha);

    m_piranha2 = new Piranha();
    m_piranha2->setPos(2975, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha2);

    m_piranha3= new Piranha();
    m_piranha3->setPos(4850, m_groundLevel - m_piranha2->boundingRect().height()-95);
    addItem(m_piranha3);

    //Add Flag Animation
    m_flag2 = new Flag();
    m_flag2->setPos(7320, m_groundLevel - m_flag2->boundingRect().height()-285);
    addItem(m_flag2);

    //Add coin counter
    m_count = new CoinCounter();
    m_count->setPos(65, m_groundLevel - m_count->boundingRect().height()-602);
    addItem(m_count);

    //Add Score counter
    m_score = new Score();
    m_score->setPos(980, m_groundLevel - m_score->boundingRect().height()-610);
    addItem(m_score);

    //Add Game Timer
    m_gameTimer = new Timer();
    m_gameTimer->setPos(1140, m_groundLevel - m_gameTimer->boundingRect().height()-610);
    addItem(m_gameTimer);

    //Add stretch
    m_stretch = new Stretch();
    m_stretch->setPos(2100, m_groundLevel - m_stretch->boundingRect().height()-20);
    addItem(m_stretch);

    //Add sign
    m_sign = new BackgroundItem(QPixmap(":images/sign.png"));
    m_sign->setPos(250, m_groundLevel - m_sign->boundingRect().height());
    addItem(m_sign);

    //Add conveyor
    m_conveyor = new Conveyor();
    m_conveyor->setPos(4160, m_groundLevel - m_conveyor->boundingRect().height()-100);
    addItem(m_conveyor);

    m_conveyor2 = new Conveyor();
    m_conveyor2->setPos(4370, m_groundLevel - m_conveyor2->boundingRect().height()-100);
    addItem(m_conveyor2);

    m_conveyor3 = new Conveyor();
    m_conveyor3->setPos(4580, m_groundLevel - m_conveyor3->boundingRect().height()-100);
    addItem(m_conveyor3);

    //Add giant goomba
    m_giantgoomba = new GiantGoomba();
    m_giantgoomba->setPos(4210, m_groundLevel - m_giantgoomba->boundingRect().height()-150);
    addItem(m_giantgoomba);

    m_giantgoomba2 = new GiantGoomba();
    m_giantgoomba2->setPos(4420, m_groundLevel - m_giantgoomba2->boundingRect().height()-150);
    addItem(m_giantgoomba2);

    m_giantgoomba3 = new GiantGoomba();
    m_giantgoomba3->setPos(4630, m_groundLevel - m_giantgoomba3->boundingRect().height()-150);
    addItem(m_giantgoomba3);

    //Add warp tube
    m_warpTube1 = new WarpTube();
    m_warpTube1->setPos(800, m_groundLevel - m_warpTube1->boundingRect().height());
    addItem(m_warpTube1);

    m_warpTube2 = new WarpTube();
    m_warpTube2->setPos(3000, m_groundLevel - m_warpTube2->boundingRect().height());
    addItem(m_warpTube2);

    m_warpTube3 = new WarpTube();
    m_warpTube3->setPos(4880, m_groundLevel - m_warpTube3->boundingRect().height());
    addItem(m_warpTube3);

    //Add Stair blocks
    m_stairBlock = new StairBlock(9);
    m_stairBlock->setPos(6750, m_groundLevel - m_stairBlock->boundingRect().height());
    addItem(m_stairBlock);

    m_stairBlock2 = new StairBlock(8);
    m_stairBlock2->setPos(6798, m_groundLevel - m_stairBlock2->boundingRect().height()-48);
    addItem(m_stairBlock2);

    m_stairBlock3 = new StairBlock(7);
    m_stairBlock3->setPos(6846, m_groundLevel - m_stairBlock3->boundingRect().height()-96);
    addItem(m_stairBlock3);

    m_stairBlock4 = new StairBlock(6);
    m_stairBlock4->setPos(6894, m_groundLevel - m_stairBlock4->boundingRect().height()-144);
    addItem(m_stairBlock4);

    m_stairBlock5 = new StairBlock(5);
    m_stairBlock5->setPos(6942, m_groundLevel - m_stairBlock5->boundingRect().height()-192);
    addItem(m_stairBlock5);

    m_stairBlock6 = new StairBlock(4);
    m_stairBlock6->setPos(6990, m_groundLevel - m_stairBlock6->boundingRect().height()-240);
    addItem(m_stairBlock6);

    m_stairBlock7 = new StairBlock(3);
    m_stairBlock7->setPos(7038, m_groundLevel - m_stairBlock7->boundingRect().height()-288);
    addItem(m_stairBlock7);

    m_stairBlock8 = new StairBlock(2);
    m_stairBlock8->setPos(7086, m_groundLevel - m_stairBlock8->boundingRect().height()-336);
    addItem(m_stairBlock8);

    //Add goomba
    m_goomba2 = new Goomba(QRectF(m_wallPlatform9->pos(), m_wallPlatform9->boundingRect().size()), -1);
    m_goomba2->setPos(5100, m_groundLevel - m_goomba2->boundingRect().height()-465);
    addItem(m_goomba2);
    connect(this->m_goomba2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));

    //Add bomb
    m_bomb2 = new Bomb(QRectF(m_wallPlatform10->pos(), m_wallPlatform10->boundingRect().size()), -1);
    m_bomb2->setPos(6100, m_groundLevel - m_bomb2->boundingRect().height()-190);
    addItem(m_bomb2);

    //Add Red Turtle
    m_redTurtle = new RedTurtle(QRectF(m_wallPlatform4->pos(), m_wallPlatform4->boundingRect().size()), -1);
    m_redTurtle->setPos(5100, m_groundLevel - m_redTurtle->boundingRect().height()+4);
    addItem(m_redTurtle);

    //Add Spiny
    m_spiny = new Spiny(QRectF(m_wallPlatform5->pos(), m_wallPlatform5->boundingRect().size()), -1);
    m_spiny->setPos(1345, m_groundLevel - m_spiny->boundingRect().height()+4);
    addItem(m_spiny);

    //add player
    m_smallPlayer = new SmallMario();
    m_smallPlayer->setPos(50, m_groundLevel - m_smallPlayer->boundingRect().height() );
    addItem(m_smallPlayer);

    //Add half castle to make it look like mario can walk inside of castle
    h_castle = new Castle();
    h_castle->setPos(7637, m_groundLevel - h_castle->boundingRect().height());
    addItem(h_castle);
}

void MyScene::controlMushroom(){

    if(bigMario){
        m_mushroom2 = new Mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else if(littleMario){
        m_mushroom2 = new Mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else if(f_ireMario){
        m_mushroom2 = new Mushroom(QRectF(mushroomQuestBox->pos(), mushroomQuestBox->boundingRect().size()), 1);
        m_mushroom2->setPos(204, m_groundLevel - m_mushroom2->boundingRect().height()-100);
        m_mushroom2->setZValue(0);
        addItem(m_mushroom2);
        connect(this->m_mushroom2, SIGNAL(marioSizeStatus(int)),this, SLOT(setMarioSize(int)));
    }
    else{
        return;
    }
}

void MyScene::controlFlower(){

    if(bigMario){
        flower = new Flower(QRectF(flowerQuestBox->pos(), flowerQuestBox->boundingRect().size()), 1);
        flower->setPos(1090, m_groundLevel - flower->boundingRect().height()-250);
        flower->setZValue(2);
        addItem(flower);
        connect(this->flower, SIGNAL(marioSizeStatusf(int)),this, SLOT(setMarioSize(int)));
    }
    else if(f_ireMario){
        flower = new Flower(QRectF(flowerQuestBox->pos(), flowerQuestBox->boundingRect().size()), 1);
        flower->setPos(1090, m_groundLevel - flower->boundingRect().height()-250);
        flower->setZValue(2);
        addItem(flower);
        connect(this->flower, SIGNAL(marioSizeStatusf(int)),this, SLOT(setMarioSize(int)));
    }
    else if(littleMario){
        return;
    }
    else{
        return;
    }
}

//Timer event for animations
void MyScene::timerEvent(QTimerEvent *){
    m_coins->nextFrame2();
    m_coins2->nextFrame2();
    m_coins3->nextFrame2();
    m_coins4->nextFrame2();
    m_coins5->nextFrame2();
    m_coins6->nextFrame2();
    m_coins7->nextFrame2();
    m_coins8->nextFrame2();
    m_coins9->nextFrame2();
    m_coins10->nextFrame2();
    m_coins11->nextFrame2();
    m_coins12->nextFrame2();
    m_coins13->nextFrame2();
    m_coins14->nextFrame2();
    m_coins15->nextFrame2();
    m_coins16->nextFrame2();
    m_coins17->nextFrame2();
    m_coins18->nextFrame2();
    m_coins19->nextFrame2();
    m_coins20->nextFrame2();
    m_coins21->nextFrame2();
    m_coins22->nextFrame2();
    m_coins23->nextFrame2();
    m_coins24->nextFrame2();
    m_coins25->nextFrame2();
    m_coins26->nextFrame2();

    m_coins27->nextFrame2();
    m_coins28->nextFrame2();
    m_coins29->nextFrame2();
    m_coins30->nextFrame2();

    m_coins32->nextFrame2();
    m_coins33->nextFrame2();
    m_coins34->nextFrame2();
    m_coins35->nextFrame2();
    m_coins36->nextFrame2();

    m_coins37->nextFrame2();
    m_coins38->nextFrame2();
    m_coins39->nextFrame2();
    m_coins40->nextFrame2();
    m_coins41->nextFrame2();
    m_coins42->nextFrame2();
    m_coins43->nextFrame2();
    m_coins44->nextFrame2();
    m_coins45->nextFrame2();
    m_coins46->nextFrame2();
    m_coins47->nextFrame2();

    m_coins48->nextFrame2();
    m_coins49->nextFrame2();
    m_coins50->nextFrame2();
    m_coins51->nextFrame2();
    m_coins52->nextFrame2();

    m_coins53->nextFrame2();
    m_coins54->nextFrame2();
    m_coins55->nextFrame2();
    m_coins56->nextFrame2();

    m_coins57->nextFrame2();
    m_coins58->nextFrame2();
    m_coins59->nextFrame2();
    m_coins60->nextFrame2();

    m_coins61->nextFrame2();
    m_coins62->nextFrame2();
    m_coins63->nextFrame2();
    m_coins64->nextFrame2();
    m_coins65->nextFrame2();
    m_coins66->nextFrame2();
    m_coins67->nextFrame2();
    m_coins68->nextFrame2();

    m_coins69->nextFrame2();
    m_coins70->nextFrame2();
    m_coins71->nextFrame2();

    m_coins72->nextFrame2();
    m_coins73->nextFrame2();
    m_coins74->nextFrame2();

    m_coins75->nextFrame2();
    m_coins76->nextFrame2();
    m_coins77->nextFrame2();
    m_coins78->nextFrame2();
    m_coins79->nextFrame2();
    m_coins80->nextFrame2();

    m_coins81->nextFrame2();
    m_coins82->nextFrame2();
    m_coins83->nextFrame2();
    m_coins84->nextFrame2();
    m_coins85->nextFrame2();
    m_coins86->nextFrame2();

    m_coins87->nextFrame2();
    m_coins88->nextFrame2();
    m_coins89->nextFrame2();
    m_coins90->nextFrame2();
    m_coins91->nextFrame2();
    m_coins92->nextFrame2();
    m_coins93->nextFrame2();
    m_coins94->nextFrame2();
    m_coins95->nextFrame2();
    m_coins96->nextFrame2();
    m_coins97->nextFrame2();
    m_coins98->nextFrame2();
    m_coins99->nextFrame2();
    m_coins100->nextFrame2();

    m_questbox->nextFrame4();
    m_questbox2->nextFrame4();
    m_questbox3->nextFrame4();
    m_questbox4->nextFrame4();
    m_questbox5->nextFrame4();
    m_questbox6->nextFrame4();
    m_questbox7->nextFrame4();
    m_questbox8->nextFrame4();
    m_questbox9->nextFrame4();
    m_questbox10->nextFrame4();
    m_questbox11->nextFrame4();
    m_questbox12->nextFrame4();

    //m_turtle->nextFrame6();
    //m_turtle2->nextFrame6();

    m_piranha->nextFrame();
    m_piranha2->nextFrame();
    m_piranha3->nextFrame();

    mBrickPlatform->nextFrame();
    mBrickPlatform2->nextFrame();
    mBrickPlatform3->nextFrame();
    mBrickPlatform4->nextFrame();
    mBrickPlatform5->nextFrame();
    mBrickPlatform6->nextFrame();
    mBrickPlatform7->nextFrame();
    mBrickPlatform8->nextFrame();

    m_NoteBox->nextFrame();
    m_NoteBox2->nextFrame();
    m_NoteBox3->nextFrame();
    m_NoteBox4->nextFrame();
    m_NoteBox5->nextFrame();
    m_NoteBox6->nextFrame();

    m_flag2->nextFrame();

    m_stretch->nextFrame();

    m_conveyor->nextFrame11();
    m_conveyor2->nextFrame11();
    m_conveyor3->nextFrame11();

    m_giantgoomba->nextFrame12();
    m_giantgoomba2->nextFrame12();
    m_giantgoomba3->nextFrame12();

    m_bomb2->nextFrame();
    m_redTurtle->nextFrame();
    m_spiny->nextFrame();
    mushroomQuestBox->nextFrame();
    flowerQuestBox->nextFrame();
}

void MyScene::playASound(){

    //emit playSound("kick");
}

void MyScene::playHitWarp(){

    emit playSound("kick");
}

qreal MyScene::jumpFactor() const{

    return m_jumpFactor;
}

void MyScene::setJumpFactor(const qreal &jumpFactor){

    if (m_jumpFactor == jumpFactor)
        return;

    m_jumpFactor = jumpFactor;
    emit jumpFactorChanged(m_jumpFactor);
}



void MyScene::checkTimer(){
    if(bigMario){
        if (0 == m_player->direction()){
            m_player->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive()){
            m_timer.start();
            m_player->walk();
        }
    }
    else if(littleMario){
        if (0 == m_smallPlayer->direction()){
            m_smallPlayer->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive()){
            m_timer.start();
            m_smallPlayer->walk();
        }
    }
    else if(f_ireMario){
        if (0 == fireMario->direction()){
            fireMario->stand();
            m_timer.stop();
        }
        else if (!m_timer.isActive()){
            m_timer.start();
            fireMario->walk();
        }
    }
}

//-------------------------------------------------------------COLLISION DETECTION-----------------------------------------------//

QGraphicsItem* MyScene::collidingPlatforms(){
    if(bigMario){
        QList<QGraphicsItem*> items =  collidingItems(m_player);
        foreach(QGraphicsItem *item, items){
            if(BrickPlatform *brickplatform = qgraphicsitem_cast<BrickPlatform *>(item)){
                return brickplatform;
            }
            if(QuestBox *questbox = qgraphicsitem_cast<QuestBox *>(item)){
                return questbox;
            }
            if(NoteBox *notebox = qgraphicsitem_cast<NoteBox *>(item)){
                return notebox;
            }
            if(WallPlatform *wallplatform = qgraphicsitem_cast<WallPlatform *>(item)){
                return wallplatform;
            }
            if(StairBlock *stairblock = qgraphicsitem_cast<StairBlock *>(item)){
                return stairblock;
            }
            if(MushroomQuestBox *mushquestbox = qgraphicsitem_cast<MushroomQuestBox *>(item)){
                return mushquestbox;
            }
            if(FlowerQuestBox *flowquestbox = qgraphicsitem_cast<FlowerQuestBox *>(item)){
                return flowquestbox;
            }
        }
        return 0;
    }
    else if(littleMario){
        QList<QGraphicsItem*> items =  collidingItems(m_smallPlayer);
        foreach(QGraphicsItem *item, items){
            if(BrickPlatform *brickplatform = qgraphicsitem_cast<BrickPlatform *>(item)){
                return brickplatform;
            }
            if(QuestBox *questbox = qgraphicsitem_cast<QuestBox *>(item)){
                return questbox;
            }
            if(NoteBox *notebox = qgraphicsitem_cast<NoteBox *>(item)){
                return notebox;
            }
            if(WallPlatform *wallplatform = qgraphicsitem_cast<WallPlatform *>(item)){
                return wallplatform;
            }
            if(StairBlock *stairblock = qgraphicsitem_cast<StairBlock *>(item)){
                return stairblock;
            }
            if(MushroomQuestBox *mushquestbox = qgraphicsitem_cast<MushroomQuestBox *>(item)){
                return mushquestbox;
            }
            if(FlowerQuestBox *flowquestbox = qgraphicsitem_cast<FlowerQuestBox *>(item)){
                return flowquestbox;
            }
        }
        return 0;
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items =  collidingItems(fireMario);
        foreach(QGraphicsItem *item, items){
            if(BrickPlatform *brickplatform = qgraphicsitem_cast<BrickPlatform *>(item)){
                return brickplatform;
            }
            if(QuestBox *questbox = qgraphicsitem_cast<QuestBox *>(item)){
                return questbox;
            }
            if(NoteBox *notebox = qgraphicsitem_cast<NoteBox *>(item)){
                return notebox;
            }
            if(WallPlatform *wallplatform = qgraphicsitem_cast<WallPlatform *>(item)){
                return wallplatform;
            }
            if(StairBlock *stairblock = qgraphicsitem_cast<StairBlock *>(item)){
                return stairblock;
            }
            if(MushroomQuestBox *mushquestbox = qgraphicsitem_cast<MushroomQuestBox *>(item)){
                return mushquestbox;
            }
            if(FlowerQuestBox *flowquestbox = qgraphicsitem_cast<FlowerQuestBox *>(item)){
                return flowquestbox;
            }
        }
        return 0;
    }
    return 0;
}

//Platform collision detection
bool MyScene::handleCollisionWithPlatform(){
    if(bigMario){
        QGraphicsItem* platform =  collidingPlatforms();
        if(platform) {
            QPointF platformPos = platform->pos();
            if(m_player->isTouchingFoot(platform)){
                m_player->setPos(m_player->pos().x(), platformPos.y() - m_player->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else{
            m_platform = 0;
        }
        return false;
    }
    else if(littleMario){
        QGraphicsItem* platform =  collidingPlatforms();
        if(platform){
            QPointF platformPos = platform->pos();
            if(m_smallPlayer->isTouchingFoot(platform)){

                m_smallPlayer->setPos(m_smallPlayer->pos().x(), platformPos.y() - m_smallPlayer->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else{
            m_platform = 0;
        }
        return false;
    }
    else if(f_ireMario){
        QGraphicsItem* platform = collidingPlatforms();
        if(platform){
            QPointF platformPos = platform->pos();
            if(fireMario->isTouchingFoot(platform)){

                fireMario->setPos(fireMario->pos().x(), platformPos.y() - fireMario->boundingRect().height());
                m_platform = platform;
                m_jumpAnimation->stop();
                return true;
            }
        }
        else{
            m_platform = 0;
        }
        return false;
    }
    return 0;
}

//Question box collision for mario head coin count
void MyScene::checkCollidingQuestBox(){

    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items){
            QuestBox* q = qgraphicsitem_cast<QuestBox*>(item);
            if(q){
                if(m_player->isTouchingHead(q)){
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario){
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items){
            QuestBox* qs = qgraphicsitem_cast<QuestBox*>(item);
            if(qs){
                if(m_smallPlayer->isTouchingHead(qs)){
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items){
            QuestBox* fs = qgraphicsitem_cast<QuestBox*>(item);
            if(fs){
                if(fireMario->isTouchingHead(fs)){
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
                }
            }
        }
    }
}

void MyScene::checkCollidingMushroomQuestBox(){

    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items) {
            MushroomQuestBox* q = qgraphicsitem_cast<MushroomQuestBox*>(item);
            if(q){
                if(m_player->isTouchingHead(q)){
                    emit spawnMushroom();
                    emit playSound("sprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario){
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items){
            MushroomQuestBox* qp = qgraphicsitem_cast<MushroomQuestBox*>(item);
            if(qp){
                if(m_smallPlayer->isTouchingHead(qp)){
                    emit spawnMushroom();
                    emit playSound("sprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items){
            MushroomQuestBox* fp = qgraphicsitem_cast<MushroomQuestBox*>(item);
            if(fp){
                if(fireMario->isTouchingHead(fp)){
                    //emit spawnMushroom();
                    emit playSound("coin");
                    m_score->increase();
                }
            }
        }
    }
}

void MyScene::scoreIncrease(int){

    m_score->increase();
}

void MyScene::checkCollidingFlag(){

if(bigMario){
    QList<QGraphicsItem*> items = collidingItems(m_player);
    foreach (QGraphicsItem* item, items) {

        Flag* f = qgraphicsitem_cast<Flag*>(item);
        if(f){

            removeItem(f);
            addItem(courseclear);
            emit playSound("stopLevelMusic");
            emit playSound("levelClear");
            levelCompleteWindow = new LevelCompleteWindow();
            levelCompleteWindow->setFixedSize(557,355);
            levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            levelCompleteWindow->exec();
        }
    }
}
else if(littleMario){
    QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
    foreach (QGraphicsItem* item, items) {

        Flag* f = qgraphicsitem_cast<Flag*>(item);
        if(f){

            removeItem(f);
            addItem(courseclear);
            emit playSound("stopLevelMusic");
            emit playSound("levelClear");
            levelCompleteWindow = new LevelCompleteWindow();
            levelCompleteWindow->setFixedSize(557,355);
            levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            levelCompleteWindow->exec();
        }
    }
}
else if(f_ireMario){
    QList<QGraphicsItem*> items = collidingItems(fireMario);
    foreach (QGraphicsItem* item, items) {

        Flag* f = qgraphicsitem_cast<Flag*>(item);
        if(f){

            removeItem(f);
            addItem(courseclear);
            emit playSound("stopLevelMusic");
            emit playSound("levelClear");
            levelCompleteWindow = new LevelCompleteWindow();
            levelCompleteWindow->setFixedSize(557,355);
            levelCompleteWindow->setWindowFlags(((levelCompleteWindow ->windowFlags() | Qt::CustomizeWindowHint)& ~Qt::WindowCloseButtonHint));
            levelCompleteWindow->exec();
         }
      }
   }
}

//Coin collision
void MyScene::checkCollidingCoin(){
    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items){
            Coin* c = qgraphicsitem_cast<Coin*>(item);
            if(c){

                removeItem(c);
                emit playSound("coin");
                m_count->increase();
                m_score->increase();
            }
        }
    }
    else if(littleMario){
            QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
            foreach (QGraphicsItem* item, items){
                Coin* c = qgraphicsitem_cast<Coin*>(item);
                if(c){
                    removeItem(c);
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();              
            }
        }
    }
    else if(f_ireMario){
            QList<QGraphicsItem*> items = collidingItems(fireMario);
            foreach (QGraphicsItem* item, items){
                Coin* c = qgraphicsitem_cast<Coin*>(item);
                if(c){
                    removeItem(c);
                    emit playSound("coin");
                    m_count->increase();
                    m_score->increase();
            }
        }
    }
}

void MyScene::checkCollidingFlowerQuestBox(){

    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items) {
            FlowerQuestBox* f = qgraphicsitem_cast<FlowerQuestBox*>(item);
            if(f){
                if(m_player->isTouchingHead(f)){
                    emit spawnFlower();
                    emit playSound("fsprout");
                    m_score->increase();
                }
            }
        }
    }
    else if(littleMario){
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items){
            FlowerQuestBox* fp = qgraphicsitem_cast<FlowerQuestBox*>(item);
            if(fp){
                if(m_smallPlayer->isTouchingHead(fp)){
                    //emit spawnFlower();
                    emit playSound("coin");
                    m_score->increase();
                }
            }
        }
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items){
            FlowerQuestBox* fp = qgraphicsitem_cast<FlowerQuestBox*>(item);
            if(fp){
                if(fireMario->isTouchingHead(fp)){
                    emit spawnFlower();
                    emit playSound("fsprout");
                    m_score->increase();
                }
            }
        }
    }
}

void MyScene::checkCollidingStairBlock(){

    if(bigMario){
        QList<QGraphicsItem*> items = collidingItems(m_player);
        foreach (QGraphicsItem* item, items) {
            StairBlock* x = qgraphicsitem_cast<StairBlock*>(item);
            if(x){

                if(x->pos().x()){
                    if(m_player->pos().x() < x->pos().x())
                        m_player->setPos(x->pos().x()- m_player->boundingRect().width()+5,m_player->pos().y());
                    if(m_player->pos().x() > x->pos().x()){
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        m_player->setPos(x->pos().x() + m_player->boundingRect().width()+370,m_player->pos().y());
                    }
                }

                if(x->pos().y()) {
                    if(m_player->pos().y() <= x->pos().y())
                        m_player->setPos(m_player->pos().x(),x->pos().y() - m_player->boundingRect().height());
                }
                if(!x->pos().y()){
                    x=0;
                }
                if(m_player->pos().y() < m_groundLevel) {

                    m_player->fall();
                    mFallTimer.start();
                    return;
                }
                m_player->setPos(m_player->pos().x(), m_player->pos().y());

            }
        }
    }
    else if(littleMario){
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items) {
            StairBlock* x = qgraphicsitem_cast<StairBlock*>(item);
            if(x){

                if(x->pos().x()){
                    if(m_smallPlayer->pos().x() < x->pos().x())
                        m_smallPlayer->setPos(x->pos().x()- m_smallPlayer->boundingRect().width()+5,m_smallPlayer->pos().y());
                    if(m_smallPlayer->pos().x() > x->pos().x()){
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        m_smallPlayer->setPos(x->pos().x() + m_smallPlayer->boundingRect().width()+370,m_smallPlayer->pos().y());
                    }
                }

                if(x->pos().y()) {
                    if(m_smallPlayer->pos().y() <= x->pos().y())
                        m_smallPlayer->setPos(m_smallPlayer->pos().x(),x->pos().y() - m_smallPlayer->boundingRect().height());
                }
                if(!x->pos().y()){
                    x=0;
                }
                if(m_smallPlayer->pos().y() < m_groundLevel) {

                    m_smallPlayer->fall();
                    mFallTimer.start();
                    return;
                }
                m_smallPlayer->setPos(m_smallPlayer->pos().x(), m_smallPlayer->pos().y());
            }
        }
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items) {
            StairBlock* x = qgraphicsitem_cast<StairBlock*>(item);
            if(x){

                if(x->pos().x()){
                    if(fireMario->pos().x() < x->pos().x())
                        fireMario->setPos(x->pos().x()- fireMario->boundingRect().width()+5,fireMario->pos().y());
                    if(fireMario->pos().x() > x->pos().x()){
                        //Bug here. I think mario is touching two different size items. This is causing a set position problem.
                        fireMario->setPos(x->pos().x() + fireMario->boundingRect().width()+370,fireMario->pos().y());
                    }
                }

                if(x->pos().y()) {
                    if(fireMario->pos().y() <= x->pos().y())
                        fireMario->setPos(fireMario->pos().x(),x->pos().y() - fireMario->boundingRect().height());
                }
                if(!x->pos().y()){
                    x=0;
                }
                if(fireMario->pos().y() < m_groundLevel) {

                    fireMario->fall();
                    mFallTimer.start();
                    return;
                }
                fireMario->setPos(fireMario->pos().x(), fireMario->pos().y());
            }
        }
    }
}

void MyScene::checkCollidingWarpTube() {
    if(bigMario){
    QList<QGraphicsItem*> items = collidingItems(m_player);
    foreach (QGraphicsItem* item, items) {

        WarpTube* w = qgraphicsitem_cast<WarpTube*>(item);
        if(w){
            if(w->pos().x()){
                if(m_player->pos().x() < w->pos().x())
                    m_player->setPos(w->pos().x()- m_player->boundingRect().width(),m_player->pos().y());
                if(m_player->pos().x() > w->pos().x()){
                    m_player->setPos(w->pos().x() + m_player->boundingRect().width()+25,m_player->pos().y());
                }
            }
        }
     }
  }
    else if(littleMario){
        QList<QGraphicsItem*> items = collidingItems(m_smallPlayer);
        foreach (QGraphicsItem* item, items) {

            WarpTube* w = qgraphicsitem_cast<WarpTube*>(item);
            if(w){
                if(w->pos().x()){
                    if(m_smallPlayer->pos().x() < w->pos().x())
                        m_smallPlayer->setPos(w->pos().x()- m_smallPlayer->boundingRect().width(),m_smallPlayer->pos().y());
                    if(m_smallPlayer->pos().x() > w->pos().x()){
                        m_smallPlayer->setPos(w->pos().x() + m_smallPlayer->boundingRect().width()+25,m_smallPlayer->pos().y());

                    }
                }
            }
        }
    }
    else if(f_ireMario){
        QList<QGraphicsItem*> items = collidingItems(fireMario);
        foreach (QGraphicsItem* item, items) {

            WarpTube* w = qgraphicsitem_cast<WarpTube*>(item);
            if(w){
                if(w->pos().x()){
                    if(fireMario->pos().x() < w->pos().x())
                        fireMario->setPos(w->pos().x()- fireMario->boundingRect().width(),fireMario->pos().y());
                    if(fireMario->pos().x() > w->pos().x()){
                        fireMario->setPos(w->pos().x() + fireMario->boundingRect().width()+25,fireMario->pos().y());

                    }
                }
            }
        }
    }
}
