/*
 * Author: equati0n
 * Date: December 2016
*/

#include "soundmanager.h"
#include "ui_soundmanager.h"
#include<QDebug>
SoundManager::SoundManager(QWidget *parent) : QDialog(parent), ui(new Ui::SoundManager){

    ui->setupUi(this);

    this->select = new QSoundEffect;
    select->setSource(QUrl("qrc:/audio/Select.wav"));
    select->setLoopCount(0);
    select->setVolume(.25f);

    this->coin = new QSoundEffect;
    coin->setSource(QUrl("qrc:/audio/coin.wav"));
    coin->setLoopCount(0);
    coin->setVolume(.25f);

    this->mario_jump = new QSoundEffect;
    mario_jump->setSource(QUrl("qrc:/audio/jump.wav"));
    mario_jump->setLoopCount(0);
    mario_jump->setVolume(.25f);

    this->mario_death = new QSoundEffect;
    mario_death->setSource(QUrl("qrc:/audio/death.wav"));
    mario_death->setLoopCount(0);
    mario_death->setVolume(.25f);

    this->levelClear = new QSoundEffect;
    levelClear->setSource(QUrl("qrc:/audio/levelclear.wav"));
    levelClear->setLoopCount(0);
    levelClear->setVolume(.25f);

    this->ghost = new QSoundEffect;
    ghost->setSource(QUrl("qrc:/audio/ghost.wav"));
    ghost->setLoopCount(0);
    ghost->setVolume(.25f);

    this->shrink = new QSoundEffect;
    shrink->setSource(QUrl("qrc:/audio/shrink.wav"));
    shrink->setLoopCount(0);
    shrink->setVolume(.25f);

    this->powerup = new QSoundEffect;
    powerup->setSource(QUrl("qrc:/audio/powerup.wav"));
    powerup->setLoopCount(0);
    powerup->setVolume(.25f);

    this->sprout = new QSoundEffect;
    sprout->setSource(QUrl("qrc:/audio/sprout.wav"));
    sprout->setLoopCount(0);
    sprout->setVolume(.25f);

    this->fsprout = new QSoundEffect;
    fsprout->setSource(QUrl("qrc:/audio/sprout.wav"));
    fsprout->setLoopCount(0);
    fsprout->setVolume(.25f);

    this->kick = new QSoundEffect;
    kick ->setSource(QUrl("qrc:/audio/kick.wav"));
    kick ->setLoopCount(0);
    kick ->setVolume(.25f);

    this->fireball = new QSoundEffect;
    fireball->setSource(QUrl("qrc:/audio/fireball.wav"));
    fireball->setLoopCount(0);
    fireball->setVolume(.25f);

    this->hitWarptube = new QSoundEffect;
    hitWarptube->setSource(QUrl("qrc:/audio/hitwarptube.wav"));
    hitWarptube->setLoopCount(0);
    hitWarptube->setVolume(.25f);

    this->level1 = new QMediaPlayer;
    level1->setMedia(QUrl("qrc:/audio/level1.mp3"));

    this->soundPlayer = new QMediaPlayer;
    soundPlayer->setMedia(QUrl("qrc:/audio/ThemeSong.mp3"));

}

SoundManager::~SoundManager(){

    delete ui;
}

void SoundManager::playSoundEffect(QString which){


    if(which == "mario_jump"){

        mario_jump->play();
    }
    else if(which == "mario_death"){

        level1->stop();
        mario_death->play();
    }
    else if(which == "coin"){

        coin->play();
    }
    else if(which == "select"){

        select->play();
    }
    else if(which == "theme"){

        //level1->stop();
        soundPlayer->play();
    }
    else if(which == "title"){

    }
    else if(which == "level1"){

        level1->play();
    }
    else if(which == "stopMusic"){

        soundPlayer->stop();
    }
    else if(which == "stopLevelMusic"){

        level1->stop();
    }
    else if(which == "levelClear"){

        levelClear->play();
    }
    else if(which == "ghost"){

        ghost->play();
    }
    else if(which == "shrink"){

        shrink->play();
    }
    else if(which == "powerup"){

        powerup->play();
    }
    else if(which == "sprout"){

        sprout->play();
    }
    else if(which == "fsprout"){

        fsprout->play();
    }
    else if(which == "kick"){

        kick->play();
    }
    else if(which == "fireball"){

        fireball->play();
    }
    else if(which == "hitWarptube"){

        hitWarptube->play();
    }
    else{
        return;
    }
}




