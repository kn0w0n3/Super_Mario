/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenuBar>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollBar>
#include <QSlider>
#include <QSoundEffect>
#include <QSpacerItem>
#include <QSpinBox>
#include <QSplashScreen>
#include <QStatusBar>
#include <QStyle>
#include "about_dialog.h"
#include "settings.h"
#include "title.h"
#include "view.h"
//#include "soundmanager.h"

class WeatherBalloon;
class WeatherStation;
class About_Dialog;
class Settings;
class Title;
class View;

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow();
    void setSize();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void playSound(QString);

private slots:
    void settings();
    void alterScreen();
    void showAbout();
    void showWeather();

public slots:

private:
    void createActions();
    void createMenus();
    void createScene();
    enum { maxState = 10 };
    Settings *setting;
    About_Dialog *about;
    Title *title;
    View *view;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QAction *returnAction;
    QAction *emptyAction;
    QAction *saveStateAction[maxState];
    QAction *loadStateAction[maxState];
    QAction *quitAction;
    QAction *fullScreenAction;
    QAction *settingsAction;
    QAction *aboutAction;
    QAction *weatherStationAction;
    QMenu *fileMenu;
    QMenu *saveSubMenu;
    QMenu *loadSubMenu;
    QMenu *viewMenu;
    QMenu *toolMenu;
    QMenu *helpMenu;
    QMenu *weatherMenu;
    QRegularExpression *myRegEx;
    WeatherStation *weatherStation;
    WeatherBalloon *weatherBalloon;
    //SoundManager *soundManager;

};
#endif // MAINWINDOW_H
