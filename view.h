/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef VIEW_H
#define VIEW_H

#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QPushButton>
class View : public QGraphicsView{
    Q_OBJECT
signals:
    void sceneChanged();

public:
    View();
    void sceneSet(QGraphicsScene *);
    QMediaPlaylist *bgm;
    QPushButton *submit;
    QLabel *uLabel;
};

#endif // VIEW_H
