#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QDialog>
#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>

namespace Ui {
class SoundManager;
}

class SoundManager : public QDialog
{
    Q_OBJECT

public:
    explicit SoundManager(QWidget *parent = 0);
    ~SoundManager();

private:
    Ui::SoundManager *ui;

    QSoundEffect *mario_jump, *mario_death, *coin, *select, *levelClear, *ghost, *shrink, *powerup, *sprout, *fsprout, *kick, *fireball, *hitWarptube;

    QMediaPlayer *soundPlayer, *level1;

signals:
    stopMusic();
public slots:
    void playSoundEffect(QString);

};
#endif // SOUNDMANAGER_H
