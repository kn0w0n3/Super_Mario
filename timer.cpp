/*
 * Author: equati0n
 * Date: December 2016
*/

#include "timer.h"
#include <QTimer>
#include <QFont>
#include<QFontDatabase>


Timer::Timer(QGraphicsItem *parent): QGraphicsTextItem(parent){

    // initialize the coinCount to 400
    timeCount = 400;

    // draw the text
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(timeCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2",30));
    startTimer(1000);

}

void Timer::timerEvent(QTimerEvent *){

    decrease();
}

void Timer::decrease(){

    if(0 != timeCount){
        timeCount--;
        setPlainText(QString("") + QString::number(timeCount));
    }

}

int Timer::getTime(){
    return timeCount;

}
