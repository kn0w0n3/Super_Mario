/*
 * Author: equati0n
 * Date: December 2016
*/

#include "view.h"

View::View() {

    bgm = new QMediaPlaylist;
    this->setFixedSize(QSize(1280, 720));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

void View::sceneSet(QGraphicsScene *scene) {

    setScene(scene);
    emit sceneChanged();
}



