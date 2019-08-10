#ifndef PLACEHOLDERSCENE_H
#define PLACEHOLDERSCENE_H

#include "mainwindow.h"
class View;

class placeHolderScene : public QGraphicsScene{
    Q_OBJECT
public:
    placeHolderScene(View *view, QWidget *parent = 0);
    QMediaPlaylist *getMusic();
private:
    QMediaPlaylist *playlist;
};

#endif // PLACEHOLDERSCENE_H
