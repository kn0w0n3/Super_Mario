/*
 * Author: equati0n
 * Date: December 2016
*/

#include "coincounter.h"
#include <QFont>
#include<QFontDatabase>

CoinCounter::CoinCounter(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the coinCount to 0
    coinCount = 0;

    // draw the text
    int id = QFontDatabase::addApplicationFont(":font/CoinCount2.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(coinCount));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2",40));
}

void CoinCounter::increase(){
    coinCount++;
    setPlainText(QString("") + QString::number(coinCount));
}

int CoinCounter::getCount(){
    return coinCount;
}
