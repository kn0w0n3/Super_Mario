/*
 * Author: equati0n
 * Date: December 2016
*/

#include "levelcompletewindow.h"
#include "ui_levelcompletewindow.h"
#include <QProcess>

LevelCompleteWindow::LevelCompleteWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelCompleteWindow)
{
    ui->setupUi(this);
}

LevelCompleteWindow::~LevelCompleteWindow(){

    delete ui;
}

void LevelCompleteWindow::on_pushButton_clicked(){

    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}

void LevelCompleteWindow::on_pushButton_2_clicked(){

    qApp->quit();
}
