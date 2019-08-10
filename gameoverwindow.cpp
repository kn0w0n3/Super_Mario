/*
 * Author: equati0n
 * Date: December 2016
*/

#include "gameoverwindow.h"
#include "ui_gameoverwindow.h"

GameOverWindow::GameOverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverWindow)
{
    ui->setupUi(this);


}

GameOverWindow::~GameOverWindow()
{
    delete ui;
}

//Yes Button restart the game
void GameOverWindow::on_pushButton_clicked(){

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());


}

//No Button quit game
void GameOverWindow::on_pushButton_2_clicked(){
    qApp->quit();

}
