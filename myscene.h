/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include <QAbstractAnimation>
#include <QDebug>
#include <QMediaPlayer>
#include "soundmanager.h"
#include "title.h"

class QGraphicsPixmapItem;
class QPropertyAnimation;
class Coin;
class BackgroundItem;
class Player;
class Castle;
class Goomba;
class QuestBox;
class Turtle;
class Piranha;
class BrickPlatform;
class QScrollBar;
class Flag;
class NoteBox;
class CoinCounter;
class Stretch;
class WallPlatform;
class Conveyor;
class GiantGoomba;
class WarpTube;
class StairBlock;
class Bomb;
class RedTurtle;
class Spiny;
class Score;
class Timer;
class SmallMario;
class Mushroom;
class GameOverWindow;
class LevelCompleteWindow;
class MushroomQuestBox;
class FireBall;
class FireMario;

class FlowerQuestBox;
class Flower;


class MyScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit MyScene(QScrollBar* s, QObject *parent = 0);
    void timerEvent(QTimerEvent *);
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void checkTimer();
    void setMarioSize(int);
    void controlMushroom();
    void controlFlower();
    void checkCollidingCoin();
    void checkCollidingQuestBox();
    void checkCollidingMushroomQuestBox();
    void checkCollidingFlowerQuestBox();
    void scoreIncrease(int);
    void checkCollidingFlag();
    void checkCollidingStairBlock();
    //void checkCollidingSpiny();
    //void checkCollidingBomb();
    //void checkCollidingTurtle();
    //void checkCollidingMushroom();
    //void checkCollidingPiranha();
    //void checkCollidingStretch();
    void checkCollidingWarpTube();
    //void checkCollidingRedTurtle();
    //void checkCollidingGiantGoomba();
    //void handleCollisionWithGoomba();
    bool handleCollisionWithPlatform();

    QGraphicsItem* collidingPlatforms();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

public slots:
   void playASound();
   void playHitWarp();


signals:
    void jumpFactorChanged(qreal);
    void playSound(QString);
    void spawnMushroom();
    void spawnFlower();
    void stopMusic();

private:
    void initPlayField();

    int m_velocity;
    qreal m_groundLevel;
    QTimer m_timer;
    QTimer mFallTimer;
    QPropertyAnimation *m_jumpAnimation;
    qreal m_jumpFactor;
    int m_jumpHeight;
    int m_fieldWidth;

    Player* m_player;
    SmallMario* m_smallPlayer;

    BackgroundItem *m_sky;
    BackgroundItem *m_Scene;
    BackgroundItem *m_ground;

    BackgroundItem *m_flag;

    BackgroundItem *m_castle;

    BackgroundItem *m_countLogo;
    BackgroundItem *m_scoreLogo;
    BackgroundItem *m_timerLogo;

    BackgroundItem *m_wall;
    BackgroundItem *m_wall2;
    BackgroundItem *m_wall3;

    BackgroundItem *gameover;
    BackgroundItem *m_sign;
    BackgroundItem *courseclear;

    Coin  *m_coins;
    Coin  *m_coins2;
    Coin  *m_coins3;
    Coin  *m_coins4;
    Coin  *m_coins5;
    Coin  *m_coins6;
    Coin  *m_coins7;
    Coin  *m_coins8;
    Coin  *m_coins9;
    Coin  *m_coins10;
    Coin  *m_coins11;
    Coin  *m_coins12;
    Coin  *m_coins13;
    Coin  *m_coins14;
    Coin  *m_coins15;
    Coin  *m_coins16;
    Coin  *m_coins17;
    Coin  *m_coins18;
    Coin  *m_coins19;
    Coin  *m_coins20;
    Coin  *m_coins21;
    Coin  *m_coins22;
    Coin  *m_coins23;
    Coin  *m_coins24;
    Coin  *m_coins25;
    Coin  *m_coins26;

    Coin  *m_coins27;
    Coin  *m_coins28;
    Coin  *m_coins29;
    Coin  *m_coins30;

    Coin  *m_coins32;
    Coin  *m_coins33;
    Coin  *m_coins34;
    Coin  *m_coins35;
    Coin  *m_coins36;

    Coin  *m_coins37;
    Coin  *m_coins38;
    Coin  *m_coins39;
    Coin  *m_coins40;
    Coin  *m_coins41;

    Coin  *m_coins42;
    Coin  *m_coins43;
    Coin  *m_coins44;
    Coin  *m_coins45;
    Coin  *m_coins46;
    Coin  *m_coins47;

    Coin  *m_coins48;
    Coin  *m_coins49;
    Coin  *m_coins50;
    Coin  *m_coins51;
    Coin  *m_coins52;

    Coin  *m_coins53;
    Coin  *m_coins54;
    Coin  *m_coins55;
    Coin  *m_coins56;

    Coin  *m_coins57;
    Coin  *m_coins58;
    Coin  *m_coins59;
    Coin  *m_coins60;

    Coin  *m_coins61;
    Coin  *m_coins62;
    Coin  *m_coins63;
    Coin  *m_coins64;
    Coin  *m_coins65;
    Coin  *m_coins66;
    Coin  *m_coins67;
    Coin  *m_coins68;

    Coin  *m_coins69;
    Coin  *m_coins70;
    Coin  *m_coins71;

    Coin  *m_coins72;
    Coin  *m_coins73;
    Coin  *m_coins74;

    Coin  *m_coins75;
    Coin  *m_coins76;
    Coin  *m_coins77;
    Coin  *m_coins78;
    Coin  *m_coins79;
    Coin  *m_coins80;

    Coin  *m_coins81;
    Coin  *m_coins82;
    Coin  *m_coins83;
    Coin  *m_coins84;
    Coin  *m_coins85;
    Coin  *m_coins86;

    Coin  *m_coins87;
    Coin  *m_coins88;
    Coin  *m_coins89;
    Coin  *m_coins90;
    Coin  *m_coins91;
    Coin  *m_coins92;
    Coin  *m_coins93;
    Coin  *m_coins94;
    Coin  *m_coins95;
    Coin  *m_coins96;
    Coin  *m_coins97;
    Coin  *m_coins98;
    Coin  *m_coins99;
    Coin  *m_coins100;

    Castle *h_castle;
    Goomba *m_goomba;
    Goomba *m_goomba2;

    QuestBox *m_questbox;
    QuestBox *m_questbox2;
    QuestBox *m_questbox3;
    QuestBox *m_questbox4;
    QuestBox *m_questbox5;
    QuestBox *m_questbox6;
    QuestBox *m_questbox7;
    QuestBox *m_questbox8;

    QuestBox *m_questbox9;
    QuestBox *m_questbox10;
    QuestBox *m_questbox11;

    QuestBox *m_questbox12;

    BrickPlatform* mBrickPlatform;
    BrickPlatform* mBrickPlatform2;
    BrickPlatform* mBrickPlatform3;
    BrickPlatform* mBrickPlatform4;
    BrickPlatform* mBrickPlatform5;
    BrickPlatform* mBrickPlatform6;
    BrickPlatform* mBrickPlatform7;
    BrickPlatform* mBrickPlatform8;

    WallPlatform *m_wallPlatform;
    WallPlatform *m_wallPlatform2;
    WallPlatform *m_wallPlatform3;
    WallPlatform *m_wallPlatform4;
    WallPlatform *m_wallPlatform5;
    WallPlatform *m_wallPlatform6;
    WallPlatform *m_wallPlatform7;
    WallPlatform *m_wallPlatform8;
    WallPlatform *m_wallPlatform9;
    WallPlatform *m_wallPlatform10;
    WallPlatform *m_wallPlatform11;

    Turtle *m_turtle;
    Turtle *m_turtle2;
    Piranha *m_piranha;
    Piranha *m_piranha2;
    Piranha *m_piranha3;

    Flag *m_flag2;
    NoteBox *m_NoteBox;
    NoteBox *m_NoteBox2;
    NoteBox *m_NoteBox3;
    NoteBox *m_NoteBox4;
    NoteBox *m_NoteBox5;
    NoteBox *m_NoteBox6;

    CoinCounter *m_count;
    Score *m_score;
    Timer *m_gameTimer;
    Stretch *m_stretch;

    Conveyor *m_conveyor;
    Conveyor *m_conveyor2;
    Conveyor *m_conveyor3;

    GiantGoomba *m_giantgoomba;
    GiantGoomba *m_giantgoomba2;
    GiantGoomba *m_giantgoomba3;

    WarpTube *m_warpTube1;
    WarpTube *m_warpTube2;
    WarpTube *m_warpTube3;

    StairBlock *m_stairBlock;
    StairBlock *m_stairBlock2;
    StairBlock *m_stairBlock3;
    StairBlock *m_stairBlock4;
    StairBlock *m_stairBlock5;
    StairBlock *m_stairBlock6;
    StairBlock *m_stairBlock7;
    StairBlock *m_stairBlock8;


    Bomb *m_bomb2;

    RedTurtle *m_redTurtle;

    Spiny *m_spiny;

    QGraphicsItem *m_platform;
    QScrollBar *scroll;
    Mushroom *m_mushroom;
    Mushroom *m_mushroom2;

    GameOverWindow *gameOverWindow;
    LevelCompleteWindow *levelCompleteWindow;

    MushroomQuestBox *mushroomQuestBox;
    FireBall *fireBall;
    FireMario *fireMario;

    SoundManager *soundManager;
    FlowerQuestBox *flowerQuestBox;
    Flower *flower;


    bool f_ireMario;
    bool bigMario;
    bool littleMario;
    bool falling;
    bool jumping;
};

#endif // MYSCENE_H
