/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef TITLE_H
#define TITLE_H

#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "mainwindow.h"
#include "myscene.h"
#include "database.h"
#include "soundmanager.h"


class View;
class LoginWindow;
class MyScene;
class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);   
    Connection createConnection();
    bool regExUserTest();

signals:
    void quitGame();
    void playSound(QString);
    //void killSound();

protected:

public slots:
    void stopMusic();

private slots:
     void login();
     void newUser();
     void developerLogin();
     void on_radioButton_toggled(bool checked);
     void quitProgram();
private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    Connection DBase;
    AnimatedGraphicsItem *background;
    View *viewer;
    QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *cursor;
    QGraphicsPixmapItem *logo;
    QGraphicsPixmapItem *border;
    QGraphicsTextItem *start;
    QGraphicsTextItem *quit;
    QMediaPlaylist *playlist;
    QPropertyAnimation *animation;
    QScrollBar *scroll;
    MyScene *scene;
    QPushButton *loginButton;
    QPushButton *newUserButton;
    QPushButton *developerButton;
    QPushButton *quitButton;
    LoginWindow *loginWindow;
    QLineEdit *userLine;
    QLineEdit *passLine;
    QLabel *userName;
    QLabel *radioText;

    QLabel *password;
    QRadioButton *radioButton;
    QSqlDatabase db;

    QRegularExpression *usernameRegEx;
    QRegularExpressionMatch *usernamenameMatch;
    QRegularExpression *passwordRegEx;
    QRegularExpressionMatch *passwordMatch;

    SoundManager *soundManager;
};
#endif // TITLE_H
