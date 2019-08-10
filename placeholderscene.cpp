#include "placeholderscene.h"

placeHolderScene::placeHolderScene(View *view, QWidget *parent){
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/music/ThemeSong.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
}

QMediaPlaylist *placeHolderScene::getMusic(){
    return playlist;
}
